#ifndef TEST_BUILD

#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/primitives.h"
#include "cameras/cameras.h"
#include "math/rectangle2d.h"
#include "math/rasterizer.h"
#include "rendering/grid-sampler.h"
#include "materials/materials.h"
#include "math/functions/noise.h"
#include "scripting/objects.h"
#include "scripting/objects/function.h"
#include "lights/light-source.h"
#include "lights/lights.h"
#include "rendering/light-ray.h"
#include "materials/brdfs/lambert.h"
#include "materials/brdfs/phong.h"
#include "meta/function-traits.h"
#include "easylogging++.h"
#include "logging.h"
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <type_traits>
#include <list>
#include <thread>
#include <atomic>

const int FRAME_COUNT = 30;
const int N_THREADS = 4;

using namespace math;
using namespace raytracer;
using namespace imaging;


struct Scene
{
    raytracer::primitives::Primitive root;
    std::vector<std::shared_ptr<lights::LightSource>> light_sources;
} scene;

std::shared_ptr<cameras::Camera> camera = nullptr;

color trace(const Ray& ray, double weight = 1.0)
{
    if (weight < 0.01)
    {
        return colors::black();
    }
    else
    {
        Hit hit;
        color result = colors::black();

        if (scene.root->find_hit(ray, &hit))
        {
            assert(hit.material);

            auto material_properties = hit.material->at(hit.local_position);

            for (auto light_source : scene.light_sources)
            {
                for (auto& light_ray : light_source->lightrays_to(hit.position))
                {
                    // Vector3D hit_to_light_source = (light_ray.ray.origin - hit.position).normalized();
                    Vector3D reflected_ray_direction = ray.direction.reflect_by(hit.normal).normalized();

                    auto incoming = light_ray.ray.direction.normalized();
                    auto outgoing = -ray.direction.normalized();
                    color reflected_color = material_properties.brdf(incoming, light_ray.color, hit.normal, outgoing);

                    result += reflected_color;

                    //Hit lighthit;
                    //if (!scene.root->find_hit(light_ray.ray, &lighthit) || lighthit.t > 0.99999)
                    //{
                    //    if (material_properties.diffuse != colors::black())
                    //    {
                    //        double diffuse_cos_angle = hit_to_light_source.dot(hit.normal);

                    //        assert(hit.normal.is_unit());
                    //        assert(-1 <= diffuse_cos_angle && diffuse_cos_angle <= 1);

                    //        if (diffuse_cos_angle > 0)
                    //        {
                    //            result += material_properties.diffuse * diffuse_cos_angle;
                    //        }
                    //    }

                    //    if (material_properties.specular != colors::black())
                    //    {
                    //        Vector3D reflected_ray_direction = ray.direction.reflect_by(hit.normal).normalized();
                    //        double specular_cos_angle = reflected_ray_direction.dot(hit_to_light_source);

                    //        if (specular_cos_angle > 0)
                    //        {
                    //            result += material_properties.specular * std::pow(specular_cos_angle, 20);
                    //        }
                    //    }                        
                    //}

                    //if (material_properties.reflectivity > 0)
                    //{
                    //    Ray reflected_ray(hit.position + reflected_ray_direction * 0.00001, reflected_ray_direction);

                    //    result += trace(reflected_ray, weight * material_properties.reflectivity) * material_properties.reflectivity;
                    //}
                }
            }
        }

        return result;
    }
}

color render_pixel(const Rasterizer& window_rasteriser, int x, int y)
{
    GridSampler sampler(1, 1);
    Rectangle2D pixel_rectangle = window_rasteriser[position(x, y)];
    color c = colors::black();
    int sample_count = 0;

    sampler.sample(pixel_rectangle, [&c, &sample_count](const Point2D& p) {
        auto ray = camera->create_ray(p);
        c += trace(ray);
        ++sample_count;
    });

    return c / sample_count;
}

Material create_lambert_material(const color& c)
{
    MaterialProperties properties;
    properties.brdf = raytracer::brdfs::lambert(c);

    return raytracer::materials::uniform(properties);
}

Material create_phong_material(const color& diffuse, const color& specular, double specular_exponent)
{
    MaterialProperties properties;
    properties.brdf = raytracer::brdfs::phong(diffuse, specular, specular_exponent);

    return raytracer::materials::uniform(properties);
}

void create_root(double t)
{
    using namespace raytracer::primitives;
    using namespace raytracer::materials;

    auto s1 = decorate(create_phong_material(colors::blue(), colors::white(), 10), sphere());
    auto plane = decorate(create_lambert_material(colors::red()), translate(Vector3D(0, -1, 0), xz_plane()));

    std::vector<Primitive> root_elts { plane, s1 };
    scene.root = group(root_elts);
}

void create_light_sources(double t)
{
    using namespace raytracer::lights;

    scene.light_sources.clear();
    scene.light_sources.push_back(omnidirectional(Point3D(0, 5, 5), colors::white()));
    // scene.light_sources.push_back(conical(Point3D(5 * t, 5, 5), Vector3D(0,-1,0), 60_degrees, colors::white()));
}

void create_scene(double t)
{
    create_root(t);
    create_light_sources(t);
}


int main()
{
    TIMED_FUNC(timerObj);

    logging::configure();

    WIF wif("e:/temp/output/test.wif");

    for (int frame = 0; frame != FRAME_COUNT; ++frame)
    {
        TIMED_SCOPE(timerObj, "single frame");

        double t = double(frame) / FRAME_COUNT;

        std::cout << "Rendering frame " << frame << std::endl;

        Bitmap bitmap(500, 500);

        camera = raytracer::cameras::perspective(Point3D(5, 5, 10), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
        // camera = raytracer::cameras::orthographic(Point3D(-5+10*t, 0, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 10, 1);
        // camera = raytracer::cameras::fisheye(Point3D(0, 0, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0), 180_degrees + 180_degrees * t, 180_degrees);

        create_scene(t);

        Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
        Rasterizer window_rasteriser(window, bitmap.width(), bitmap.height());

        bitmap.clear(colors::black());

        if (N_THREADS > 1)
        {
            std::atomic<unsigned> j(0);
            std::vector<std::thread> threads;

            for (int k = 0; k != N_THREADS; ++k)
            {
                threads.push_back(std::thread([&]() {
                    unsigned current;

                    while ((current = j++) < bitmap.height())
                    {
                        int y = bitmap.height() - current - 1;

                        for (int i = 0; i != bitmap.width(); ++i)
                        {
                            int x = i;

                            color c = render_pixel(window_rasteriser, x, y);

                            bitmap[position(i, current)] = c;
                        }
                    }
                }));
            }

            for (auto& thread : threads)
            {
                thread.join();
            }
        }
        else
        {
            for (int j = 0; j != bitmap.height(); ++j)
            {
                int y = bitmap.height() - j - 1;

                for (int i = 0; i != bitmap.width(); ++i)
                {
                    int x = i;

                    color c = render_pixel(window_rasteriser, x, y);

                    bitmap[position(i, j)] = c;
                }
            }
        }

        wif.write_frame(bitmap);
    }
}

#endif
