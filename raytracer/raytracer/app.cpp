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
};

std::shared_ptr<cameras::Camera> camera = nullptr;

class RayTracer
{
public:
    virtual color trace(const Scene&, const Ray&) const = 0;
    };

class FastRayTracer : public RayTracer
{
public:
    FastRayTracer(unsigned recursion_limit = 2)
        : m_recursion_limit(recursion_limit) { }

    color trace(const Scene& scene, const Ray& ray) const override
    {
        return trace(scene, ray, m_recursion_limit);
    }

private:
    color trace(const Scene& scene, const Ray& ray, unsigned recursions_left) const
    {
        if (!recursions_left)
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
                        Vector3D reflected_ray_direction = ray.direction.reflect_by(hit.normal).normalized();
                        auto direction_back_to_eye = -ray.direction.normalized();

                        Hit lighthit;

                        if (!scene.root->find_hit(light_ray.ray, &lighthit) || lighthit.t > 0.99999)
                        {
                            auto incoming = light_ray.ray.direction.normalized();
                            color reflected_color = material_properties.brdf(incoming, light_ray.color, hit.normal, direction_back_to_eye);

                            result += reflected_color;
                        }

                        Ray reflected_ray(hit.position + 0.00001 * reflected_ray_direction, reflected_ray_direction);
                        color reflection_color = trace(scene, reflected_ray, recursions_left - 1);
                        result += material_properties.brdf(-reflected_ray_direction, reflection_color, hit.normal, direction_back_to_eye);
                    }
                }
            }

            return result;
        }
    }

    unsigned m_recursion_limit;
};

class MonteCarloRayTracer : public RayTracer
{
public:
    MonteCarloRayTracer(unsigned recursion_limit = 2)
        : m_recursion_limit(recursion_limit) { }

    color trace(const Scene& scene, const Ray& ray) const override
    {
        return trace(scene, ray, m_recursion_limit);
    }

private:
    color trace(const Scene& scene, const Ray& ray, unsigned recursions_left) const
    {
        if (!recursions_left)
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
                        Vector3D reflected_ray_direction = ray.direction.reflect_by(hit.normal).normalized();
                        auto direction_back_to_eye = -ray.direction.normalized();

                        Hit lighthit;

                        if (!scene.root->find_hit(light_ray.ray, &lighthit) || lighthit.t > 0.99999)
                        {
                            auto incoming = light_ray.ray.direction.normalized();

                            color reflected_color = material_properties.brdf(incoming, light_ray.color, hit.normal, direction_back_to_eye);

                            result += reflected_color;
                        }

                        int count = 0;
                        color total = colors::black();

                        for (double azimuth = 0; azimuth < 360; azimuth += 10)
                        {
                            for (double altitude = -90; altitude <= 90; altitude += 10)
                            {
                                Vector3D direction(1, degrees(azimuth), degrees(altitude));

                                if (direction.dot(hit.normal) > 0)
                                {
                                    Ray r(hit.position + 0.00001 * direction, direction);
                                    color c = trace(scene, r, recursions_left - 1);

                                    total += material_properties.brdf(-direction, c, hit.normal, direction_back_to_eye);
                                    ++count;
                                }
                            }
                        }

                        result += (total / count);
                    }
                }
            }

            return result;
        }
    }

    unsigned m_recursion_limit;
};

color render_pixel(const Rasterizer& window_rasteriser, int x, int y, const Scene& scene, const RayTracer& ray_tracer)
{
    GridSampler sampler(1, 1);
    Rectangle2D pixel_rectangle = window_rasteriser[position(x, y)];
    color c = colors::black();
    int sample_count = 0;

    sampler.sample(pixel_rectangle, [&c, &sample_count, &scene, &ray_tracer](const Point2D& p) {
        auto ray = camera->create_ray(p);
        c += ray_tracer.trace(scene, ray);
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

raytracer::primitives::Primitive create_root(double t)
{
    using namespace raytracer::primitives;
    using namespace raytracer::materials;

    auto s1 = decorate(create_phong_material(colors::blue() * 0.5, colors::white() * 0.5, 10), sphere());
    auto plane = decorate(create_lambert_material(colors::red() * 0.5), translate(Vector3D(0, -1, 0), xz_plane()));

    std::vector<Primitive> root_elts{ plane, s1 };
    return group(root_elts);
}

std::vector<std::shared_ptr<raytracer::lights::LightSource>> create_light_sources(double t)
{
    using namespace raytracer::lights;

    std::vector<std::shared_ptr<LightSource>> light_sources;

    light_sources.push_back(omnidirectional(Point3D(5 * t, 5, 5), colors::white()));
    // scene.light_sources.push_back(conical(Point3D(5 * t, 5, 5), Vector3D(0,-1,0), 60_degrees, colors::white()));

    return light_sources;
}

std::shared_ptr<Scene> create_scene(double t)
{
    auto scene = std::make_shared<Scene>();

    scene->root = create_root(t);
    scene->light_sources = create_light_sources(t);

    return scene;
}


int main()
{
    TIMED_FUNC(timerObj);

    logging::configure();

    WIF wif("e:/temp/output/test.wif");

    FastRayTracer ray_tracer;


    for (int frame = 0; frame != FRAME_COUNT; ++frame)
    {
        TIMED_SCOPE(timerObj, "single frame");

        double t = double(frame) / FRAME_COUNT;

        std::cout << "Rendering frame " << frame << std::endl;

        Bitmap bitmap(500, 500);

        camera = raytracer::cameras::perspective(Point3D(5, 5, 10), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
        // camera = raytracer::cameras::orthographic(Point3D(-5+10*t, 0, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 10, 1);
        // camera = raytracer::cameras::fisheye(Point3D(0, 0, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0), 180_degrees + 180_degrees * t, 180_degrees);

        auto scene = create_scene(t);

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

                            color c = render_pixel(window_rasteriser, x, y, *scene, ray_tracer);

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

                    color c = render_pixel(window_rasteriser, x, y, *scene, ray_tracer);

                    bitmap[position(i, j)] = c;
                }
            }
        }

        wif.write_frame(bitmap);
    }
}

#endif
