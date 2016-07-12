#ifndef TEST_BUILD

#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/primitives.h"
#include "cameras/cameras.h"
#include "math/rasterizer.h"
#include "sampling/grid-sampler.h"
#include "materials/materials.h"
#include "math/functions/noise.h"
#include "lights/lights.h"
#include "lights/light-ray.h"
#include "materials/brdfs/lambert.h"
#include "materials/brdfs/phong.h"
#include "materials/worley-material.h"
#include "raytracing/ray-tracer.h"
#include "raytracing/fast-ray-tracer.h"
#include "rendering/multithreaded-renderer.h"
#include "animation/animation.h"
#include "easylogging++.h"
#include "logging.h"
#include "util/lazy.h"
#include "chai/scripting.h"
#include <assert.h>


#ifdef NDEBUG
const int BITMAP_SIZE = 500;
const int FRAME_COUNT = 30;
const int FRAME_START = 0;
const int FRAME_END = 1;
const int SAMPLES = 2;
const int N_THREADS = 4;
#else
const int BITMAP_SIZE = 500;
const int FRAME_COUNT = 30;
const int FRAME_START = 0;
const int FRAME_END = 1;
const int SAMPLES = 1;
const int N_THREADS = 1;
#endif

using namespace math;
using namespace raytracer;
using namespace imaging;
using namespace animation;


Material create_lambert_material(const color& c, bool reflective = false)
{
    MaterialProperties properties;
    properties.ambient = colors::black();
    properties.diffuse = c;
    properties.specular = colors::black();
    properties.specular_exponent = 0;
    properties.reflectivity = 0;

    return raytracer::materials::uniform(properties);
}

Material create_phong_material(const color& diffuse, const color& specular, double specular_exponent, double reflectivity)
{
    MaterialProperties properties;
    properties.ambient = colors::black();
    properties.diffuse = diffuse;
    properties.specular = specular;
    properties.specular_exponent = specular_exponent;
    properties.reflectivity = reflectivity;

    return raytracer::materials::uniform(properties);
}

Lazy<raytracer::primitives::Primitive> bunny([]() { return raytracer::primitives::fast_mesh(std::ifstream("e:/temp/bunny.mesh")); });
Lazy<raytracer::primitives::Primitive> buddha([]() { return raytracer::primitives::fast_mesh(std::ifstream("e:/temp/buddha.mesh")); });
Lazy<raytracer::primitives::Primitive> dragon([]() { return raytracer::primitives::fast_mesh(std::ifstream("e:/temp/buddha.dragon")); });
Lazy<raytracer::primitives::Primitive> statuette([]() { return raytracer::primitives::fast_mesh(std::ifstream("e:/temp/statuette.mesh")); });
Lazy<raytracer::primitives::Primitive> lucy([]() { return raytracer::primitives::fast_mesh(std::ifstream("e:/temp/lucy.mesh")); });

raytracer::primitives::Primitive create_root(TimeStamp now)
{
    using namespace raytracer::primitives;
    using namespace raytracer::materials;

    std::vector<Primitive> primitives;
    // primitives.push_back(sphere());

    auto vans = checkered(
        create_phong_material(colors::white() * 0.85, colors::white() * 0.85, 100, 0.0),
        create_phong_material(colors::white() * 0.1, colors::white() * 0.85, 8, 0.0));

    // auto g = decorate(create_lambert_material(colors::white() * 0.85), cone_along_z());
    // auto g = decorate(create_phong_material(colors::white()*0.5, colors::white(), 10, true), bunny.value() );
    // auto p = decorate(create_phong_material(colors::white()*0.5, colors::white(), 10, false), translate(Vector3D(0, g->bounding_box().z().lower, 0), xz_plane()));
    auto g = decorate(vans, translate(Vector3D(0, -1, 0), xz_plane()));

    std::vector<Primitive> spheres;

    for (double z = 0; z < 20; z += 5)
    {
        spheres.push_back(translate(Vector3D(-2, 0, -z), sphere()));
        spheres.push_back(translate(Vector3D(2, 0, -z), sphere()));
    }

    auto g2 = decorate(vans, accelerated_union(spheres));

    // auto g = group(primitives);
    std::vector<Primitive> root_elts{ g, g2 };



    return group(root_elts);
}

std::vector<raytracer::lights::LightSource> create_light_sources(TimeStamp now)
{
    using namespace raytracer::lights;

    std::vector<LightSource> light_sources;

    // light_sources.push_back(omnidirectional(Point3D(5, 5, 0), colors::white()));
    // light_sources.push_back(spot(light_position, Point3D(0, 0, 0), 60_degrees, colors::white()));
    // light_sources.push_back(directional(Vector3D(1, 45_degrees, -45_degrees), colors::white()));
    light_sources.push_back(area(Rectangle3D(Point3D(-0.5, 3, 5.5), Vector3D(1, 0, 0), Vector3D(0, 0, 1)), samplers::grid(3, 3), colors::white()));

    return light_sources;
}

raytracer::cameras::Camera create_camera(TimeStamp now)
{
    // auto camera_position_animation = circular(Point3D(0, 1, 5), Point3D(0, 0, 0), Vector3D::y_axis(), Interval<Angle>(0_degrees, 360_degrees), 1_s);
    Point3D camera_position(0, 1, 5);
    // Point3D camera_position = camera_position_animation(now);
    auto camera = raytracer::cameras::perspective(camera_position, Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
    // auto camera = raytracer::cameras::orthographic(Point3D(-5+10*t, 0, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 10, 1);
    // auto camera = raytracer::cameras::fisheye(Point3D(0, 0, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0), 180_degrees + 180_degrees * t, 180_degrees);
    // auto camera = raytracer::cameras::depth_of_field_perspective(camera_position, Point3D(0, 1, -5 * now.seconds()), Vector3D(0, 1, 0), 1, 1, 0.5, samplers::grid(4, 4));

    return camera;
}

std::shared_ptr<Scene> create_scene(TimeStamp now)
{
    auto scene = std::make_shared<Scene>();

    scene->root = create_root(now);
    scene->light_sources = create_light_sources(now);
    scene->camera = create_camera(now);

    return scene;
}

//Bitmap render_picture(Renderer const Scene& scene)
//{
//    auto ray_tracer = raytracer::raytracers::fast_ray_tracer();
//    auto renderer = raytracer::rendering::multithreaded(BITMAP_SIZE, BITMAP_SIZE, raytracer::samplers::grid(SAMPLES, SAMPLES), ray_tracer, N_THREADS);
//
//    return renderer->render(scene);
//}

void render()
{
    TIMED_FUNC(timerObj);

    logging::configure();

    WIF wif("e:/temp/output/test.wif");

    auto ray_tracer = raytracer::raytracers::fast_ray_tracer();
    auto renderer = raytracer::rendering::multithreaded(BITMAP_SIZE, BITMAP_SIZE, raytracer::samplers::grid(SAMPLES, SAMPLES), ray_tracer, N_THREADS);

    for (int frame = FRAME_START; frame < FRAME_END; ++frame)
    {
        TIMED_SCOPE(timerObj, "single frame");

        double t = double(frame) / FRAME_COUNT;
        TimeStamp now = TimeStamp::from_epoch(1_s * t);
        auto scene = create_scene(now);

        std::cout << "Rendering frame " << frame << std::endl;

        auto bitmap = renderer->render(*scene);

        wif.write_frame(bitmap);
    }
}

int main()
{
    render();
}

#endif
