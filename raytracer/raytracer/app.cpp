#ifndef TEST_BUILD

#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/primitives.h"
#include "cameras/cameras.h"
#include "math/rasterizer.h"
#include "math/functions/functions.h"
#include "math/functions/noise.h"
#include "sampling/grid-sampler.h"
#include "materials/materials.h"
#include "lights/lights.h"
#include "raytracing/ray-tracers.h"
#include "rendering/single-threaded-renderer.h"
#include "rendering/multithreaded-renderer.h"
#include "rendering/cartoon-renderer.h"
#include "animation/animation.h"
#include "demo/demos.h"
#include "easylogging++.h"
#include "logging.h"
#include "util/lazy.h"
#include "math/point.h"
// #include "chai/scripting.h"
#include <assert.h>


#ifdef NDEBUG
const int BITMAP_SIZE = 500;
const int FRAME_COUNT = 30 * 1;
const int FRAME_START = 0;
const int FRAME_END = FRAME_COUNT;
const int SAMPLES = 2;
const int N_THREADS = 4;
#else
const int BITMAP_SIZE = 100;
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
    MaterialProperties properties(colors::black(), c, colors::black(), 0, 0, 0, 0);

    return raytracer::materials::uniform(properties);
}

Material create_phong_material(const color& ambient, const color& diffuse, const color& specular, double specular_exponent, double reflectivity)
{
    MaterialProperties properties(ambient, diffuse, specular, specular_exponent, reflectivity, 0, 0);

    return raytracer::materials::uniform(properties);
}

Material create_phong_material(const color& ambient, const color& diffuse, const color& specular, double specular_exponent, double reflectivity, double transparency, double refractive_index)
{
    MaterialProperties properties(ambient, diffuse, specular, specular_exponent, reflectivity, transparency, refractive_index);

    return raytracer::materials::uniform(properties);
}

Lazy<raytracer::Primitive> bunny([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/bunny.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> buddha([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/buddha.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> dragon([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/dragon.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> statuette([]() { return raytracer::primitives::fast_mesh(std::ifstream("e:/temp/statuette.mesh")); });
Lazy<raytracer::Primitive> lucy([]() { return raytracer::primitives::fast_mesh(std::ifstream("e:/temp/lucy.mesh")); });

raytracer::Primitive create_root(TimeStamp now)
{
    using namespace raytracer::primitives;
    using namespace raytracer::materials;

    std::vector<Primitive> primitives;

    auto b = decorate(marble3d(4, 10), sphere());
    // auto plane = decorate(wood2d(4, 0.4), translate(Vector3D(0, -1, 0), xz_plane()));

    return make_union(std::vector<Primitive> { b });
}

std::vector<raytracer::LightSource> create_light_sources(TimeStamp now)
{
    using namespace raytracer::lights;

    std::vector<LightSource> light_sources;

    Point3D light_position = point(0, 5, 5);
    light_sources.push_back(omnidirectional(light_position, colors::white()));
    // light_sources.push_back(spot(light_position, Point3D(0, 0, 0), 60_degrees, colors::white()));
    // light_sources.push_back(directional(Vector3D(1, 45_degrees, -45_degrees), colors::white()));
    // light_sources.push_back(area(Rectangle3D(Point3D(-0.5, 3, 5.5), Vector3D(1, 0, 0), Vector3D(0, 0, 1)), samplers::grid(3, 3), colors::white()));

    return light_sources;
}

raytracer::Camera create_camera(TimeStamp now)
{
    using namespace math::functions::easing;

    // auto camera_position_animation = circular(Point3D(0, 1, 5), Point3D(0, 0, 0), Vector3D::y_axis(), Interval<Angle>(0_degrees, 360_degrees), 1_s);

    math::Function<double, double> t = math::functions::identity<double>();
    Animation<double> camera_x = ease(make_animation(-2.5 + 5.0 * t, 1_s), easing_function<QUADRATIC, INOUT>());
    Point3D camera_position = point(camera_x(now), 1, 5);
    auto camera = raytracer::cameras::perspective(camera_position, point(0, 0, 0), vector(0, 1, 0), 1, 1);
    // auto camera = raytracer::cameras::orthographic(Point3D(-5+10*t, 0, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 10, 1);
    // auto camera = raytracer::cameras::fisheye(Point3D(0, 0, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0), 180_degrees + 180_degrees * t, 180_degrees);
    // auto camera = raytracer::cameras::depth_of_field_perspective(camera_position, Point3D(0, 1, -5 * now.seconds()), Vector3D(0, 1, 0), 1, 1, 0.5, samplers::grid(4, 4));

    return camera;
}

Animation<std::shared_ptr<Scene>> create_scene()
{
    std::function<std::shared_ptr<Scene>(TimeStamp)> lambda = [](TimeStamp now) -> std::shared_ptr<Scene> {
        auto camera = create_camera(now);
        auto root = create_root(now);
        auto light_sources = create_light_sources(now);
        auto scene = std::make_shared<Scene>(camera, root, light_sources);

        return scene;
    };

    return make_animation<std::shared_ptr<Scene>>(from_lambda<std::shared_ptr<Scene>, TimeStamp>(lambda), Duration::from_seconds(1));
}

void render_animation(Animation<std::shared_ptr<Scene>> scene_animation, unsigned fps)
{
    std::string output_path = "e:/temp/output/test.wif";
    WIF wif(output_path);

    auto ray_tracer = raytracer::raytracers::v6();

    auto renderer = N_THREADS > 1 ? raytracer::rendering::multithreaded(BITMAP_SIZE, BITMAP_SIZE, raytracer::samplers::grid(2, 2), ray_tracer, N_THREADS) :
        raytracer::rendering::single_threaded(BITMAP_SIZE, BITMAP_SIZE, raytracer::samplers::grid(SAMPLES, SAMPLES), ray_tracer);
    // auto renderer = raytracer::rendering::cartoon(BITMAP_SIZE, BITMAP_SIZE, raytracer::samplers::grid(2, 2), ray_tracer, N_THREADS, 4, 0.005);

    for (int frame = 0; frame < scene_animation.duration().seconds() * fps; ++frame)
    {
        TIMED_SCOPE(timerObj, "single frame");

        double t = double(frame) / FRAME_COUNT;
        TimeStamp now = TimeStamp::from_epoch(1_s * t);
        auto scene = scene_animation(now);

        std::cout << "Rendering frame " << frame << std::endl;

        auto bitmap = renderer->render(*scene);

        wif.write_frame(bitmap);
    }
}

void render()
{
    logging::configure();

    render_animation(create_scene(), 1);
}

int main()
{
    TIMED_FUNC(timerObj);

    // render();
    // scripting::run_script("e:/repos/ucll/3dcg/raytracer2/scripts/test.chai");

    Point<3> p = math::point(1, 2, 3);
    Point<3> q = math::point(4, 5, 6);
}

#endif
