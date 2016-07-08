#ifndef TEST_BUILD

#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/primitives.h"
#include "cameras/cameras.h"
#include "math/rasterizer.h"
#include "rendering/grid-sampler.h"
#include "materials/materials.h"
#include "math/functions/noise.h"
#include "scripting/objects.h"
#include "scripting/objects/function.h"
#include "lights/lights.h"
#include "rendering/light-ray.h"
#include "materials/brdfs/lambert.h"
#include "materials/brdfs/phong.h"
#include "materials/worley-material.h"
#include "raytracing/ray-tracer.h"
#include "raytracing/fast-ray-tracer.h"
#include "animation/animation.h"
#include "easylogging++.h"
#include "logging.h"
#include "util/lazy.h"
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <type_traits>
#include <list>
#include <thread>
#include <atomic>
#include <sstream>

const int BITMAP_SIZE = 500;
const int FRAME_COUNT = 30;
const int FRAME_START = 0;
const int FRAME_END = FRAME_COUNT;
const int SAMPLES = 1;

#ifdef NDEBUG
const int N_THREADS = 4;
#else
const int N_THREADS = 1;
#endif

using namespace math;
using namespace raytracer;
using namespace imaging;
using namespace animation;

std::shared_ptr<cameras::Camera> camera = nullptr;

color render_pixel(const Rasterizer& window_rasteriser, int x, int y, const Scene& scene, const RayTracer& ray_tracer)
{
    GridSampler sampler(SAMPLES, SAMPLES);
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

Material create_lambert_material(const color& c, bool reflective = false)
{
    MaterialProperties properties;
    properties.brdf = raytracer::brdfs::lambert(c);
    properties.reflective = reflective;

    return raytracer::materials::uniform(properties);
}

Material create_phong_material(const color& diffuse, const color& specular, double specular_exponent, bool reflective = true)
{
    MaterialProperties properties;
    properties.brdf = raytracer::brdfs::phong(diffuse, specular, specular_exponent);
    properties.reflective = reflective;

    return raytracer::materials::uniform(properties);
}

Lazy<raytracer::primitives::Primitive> bunny([]() { return raytracer::primitives::fast_mesh(std::ifstream("e:/temp/bunny.mesh")); });
Lazy<raytracer::primitives::Primitive> buddha([]() { return raytracer::primitives::load_mesh(std::ifstream("e:/temp/buddha.mesh")); });
Lazy<raytracer::primitives::Primitive> statuette([]() { return raytracer::primitives::load_mesh(std::ifstream("e:/temp/statuette.mesh")); });
Lazy<raytracer::primitives::Primitive> lucy([]() { return raytracer::primitives::load_mesh(std::ifstream("e:/temp/lucy.mesh")); });

raytracer::primitives::Primitive create_root(TimeStamp now)
{
    using namespace raytracer::primitives;
    using namespace raytracer::materials;

    std::vector<Primitive> primitives;
    // primitives.push_back(sphere());

    auto g = decorate(create_lambert_material(colors::white() * 0.85), bunny.value());
    // auto g = decorate(materials::worley(), bunny.value() );
    // auto p = decorate(create_phong_material(colors::white()*0.5, colors::white(), 10, false), translate(Vector3D(0, g->bounding_box().z().lower, 0), xz_plane()));
    // auto p = decorate(create_lambert_material(colors::white()*0.5), translate(Vector3D(0, -1, 0), xz_plane()));

    // auto g = group(primitives);
    std::vector<Primitive> root_elts{ g };
    return group(root_elts);
}

std::vector<std::shared_ptr<raytracer::lights::LightSource>> create_light_sources(TimeStamp now)
{
    using namespace raytracer::lights;

    std::vector<std::shared_ptr<LightSource>> light_sources;

    Point3D light_position(0, 1, 5);
    // Point3D light_position = circular_xz(5, Interval<Angle>(90_degrees, 450_degrees), Interval<TimeStamp>(TimeStamp::zero(), TimeStamp::zero() + 1_s))(now) + Vector3D(0, 2, 0);
    light_sources.push_back(omnidirectional(light_position, colors::white()));

    // light_sources.push_back(spot(light_position, Point3D(0, 0, 0), 60_degrees, colors::white()));

    // light_sources.push_back(directional(Vector3D(1, 45_degrees, -45_degrees), colors::white()));

    return light_sources;
}

std::shared_ptr<Scene> create_scene(TimeStamp now)
{
    auto scene = std::make_shared<Scene>();

    scene->root = create_root(now);
    scene->light_sources = create_light_sources(now);

    return scene;
}

int main()
{
    TIMED_FUNC(timerObj);

    logging::configure();

    WIF wif("e:/temp/output/test.wif");

    auto ray_tracer = raytracer::raytracers::fast_ray_tracer();

    for (int frame = FRAME_START; frame != FRAME_END; ++frame)
    {
        TIMED_SCOPE(timerObj, "single frame");

        double t = double(frame) / FRAME_COUNT;
        TimeStamp now = TimeStamp::zero() + 1_s * t;

        std::cout << "Rendering frame " << frame << std::endl;

        Bitmap bitmap(BITMAP_SIZE, BITMAP_SIZE);

        auto camera_position = circular_xz(1, Interval<Angle>(90_degrees, 450_degrees), Interval<TimeStamp>(TimeStamp::zero(), TimeStamp::zero() + 1_s))(now) + Vector3D(0, 1, 0);
        // Point3D camera_position(0, 2+t, 2);
        camera = raytracer::cameras::perspective(Point3D(0, 0, 4), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
        // camera = raytracer::cameras::orthographic(Point3D(-5+10*t, 0, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 10, 1);
        // camera = raytracer::cameras::fisheye(Point3D(0, 0, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0), 180_degrees + 180_degrees * t, 180_degrees);

        auto scene = create_scene(now);

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

                            color c = render_pixel(window_rasteriser, x, y, *scene, *ray_tracer);

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
                std::ostringstream ss;
                ss << "line " << j << " out of " << bitmap.height();
                TIMED_SCOPE(timerObj, ss.str());

                int y = bitmap.height() - j - 1;

                for (int i = 0; i != bitmap.width(); ++i)
                {
                    int x = i;

                    color c = render_pixel(window_rasteriser, x, y, *scene, *ray_tracer);

                    bitmap[position(i, j)] = c;
                }
            }
        }

        wif.write_frame(bitmap);
    }
}

#endif
