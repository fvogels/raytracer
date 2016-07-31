#ifndef TEST_BUILD

#include "imaging/bitmap.h"
#include "imaging/wif-format.h"
#include "primitives/primitives.h"
#include "cameras/cameras.h"
#include "math/rasterizer.h"
#include "math/functions.h"
#include "math/functions/noise.h"
#include "sampling/grid-sampler.h"
#include "materials/materials.h"
#include "lights/lights.h"
#include "raytracing/ray-tracers.h"
#include "rendering/renderers.h"
#include "rendering/cartoon-renderer.h"
#include "animation/animation.h"
#include "demo/demos.h"
#include "logging.h"
#include "util/lazy.h"
#include "math/point.h"
#include "imaging/bitmap-function.h"
#include "pipeline/pipelines.h"
#include "util/looper.h"
// #include "scripting/scripting.h"
#include "easylogging++.h"
#include <assert.h>
#include <type_traits>
#include <list>

#ifdef NDEBUG
const int BITMAP_SIZE = 500;
const int SAMPLES = 1;
const int N_THREADS = 4;
#else
const int BITMAP_SIZE = 100;
const int SAMPLES = 1;
const int N_THREADS = 1;
#endif

using namespace math;
using namespace raytracer;
using namespace imaging;
using namespace animation;
using namespace util;


Lazy<raytracer::Primitive> bunny([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/bunny.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> buddha([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/buddha.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> dragon([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/dragon.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> statuette([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/statuette.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> lucy([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/lucy.bmesh", std::ios::binary)); });

raytracer::Primitive create_root(TimeStamp now)
{
    using namespace raytracer::primitives;
    using namespace raytracer::materials;

    std::vector<Primitive> primitives;

    auto position_animation = animation::ease(animation::straight(Point3D(-2, 0, 0), Point3D(2, 0, 0), Duration::from_seconds(1)), math::functions::easing::easing_function<math::functions::easing::QUADRATIC, math::functions::easing::out>());
    // auto b = group(1, decorate(uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.5, 0, 1.5)), bunny.value()));
    // auto s = decorate(materials::texture("e:/temp/earth2.bmp"), translate(Vector3D(0,now.seconds(), 0), sphere()));

    auto p = decorate(
        uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::black(), 0, 0, 0, 0)),
        translate(Vector3D(0, 0, -10), xy_plane()));
    auto s = group(1, decorate(
        uniform(MaterialProperties(colors::red() * 0.1, colors::red() * 0.8, colors::white(), 20, 0, 0, 0)),
        translate(Vector3D(0, 0, 0), sphere())));

    auto s2 = group(2, decorate(
        uniform(MaterialProperties(colors::green() * 0.1, colors::green() * 0.8, colors::white(), 20, 0, 0, 0)),
        translate(Vector3D(-2, 0, -2), sphere())));

    auto s3 = group(2, decorate(
        uniform(MaterialProperties(colors::blue() * 0.1, colors::blue() * 0.8, colors::white(), 20, 0, 0, 0)),
        translate(Vector3D(2, 1, 0), sphere())));

    return make_union(std::vector<Primitive> { p, s, s2, s3 });
}

std::vector<raytracer::LightSource> create_light_sources(TimeStamp now)
{
    using namespace raytracer::lights;

    std::vector<LightSource> light_sources;

    Point3D light_position = point(0, 0, 5);
    light_sources.push_back(omnidirectional(light_position, colors::white()));
    // light_sources.push_back(spot(light_position, Point3D(0, 0, 0), 120_degrees, colors::white()));
    // light_sources.push_back(directional(Vector3D(1, 45_degrees, -45_degrees), colors::white()));
    // light_sources.push_back(area(Rectangle3D(Point3D(-0.5, 3, 5.5), Vector3D(1, 0, 0), Vector3D(0, 0, 1)), samplers::grid(3, 3), colors::white()));


   /* std::function<Color(Angle, Angle)> lambda = [=](Angle x, Angle y) -> Color {
        double a = x.degrees() / 12;
        double b = y.degrees() / 12;

        if (a - round(a) < 0.1 || b - round(b) < 0.1)
        {
            return colors::black();
        }
        else
        {
            return colors::white();
        }
    };

    light_sources.push_back(anisotropic(light_position, Point3D(0, 0, 0), Vector3D(1, 1, 1).normalized(), from_lambda(lambda)));
*/
    return light_sources;
}

raytracer::Camera create_camera(TimeStamp now)
{
    using namespace math::functions::easing;

    // auto camera_position_animation = circular(Point3D(0, 1, 5), Point3D(0, 0, 0), Vector3D::y_axis(), Interval<Angle>(0_degrees, 360_degrees), 1_s);

    auto camera_position_animation = circular(point(0, 0, 5), point(0, 0, 0), vector(0, 1, 0).normalized(), math::Interval<Angle>(0_degrees, 360_degrees), Duration::from_seconds(1));
    Point3D camera_position(0.5, 0.5, 5);
    auto camera = raytracer::cameras::perspective(camera_position, point(0, 0, 0), vector(0, 1, 0), 1, 1);
    // auto camera = raytracer::cameras::orthographic(Point3D(-5+10*t, 0, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 10, 1);
    // auto camera = raytracer::cameras::fisheye(Point3D(0, 0, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0), 180_degrees + 180_degrees * t, 180_degrees);
    // auto camera = raytracer::cameras::depth_of_field_perspective(camera_position, Point3D(0, 1, -5 * now.seconds()), Vector3D(0, 1, 0), 1, 1, 0.5, samplers::grid(4, 4));

    return camera;
}

Animation<std::shared_ptr<Scene>> create_scene_animation()
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

void render()
{
    using namespace raytracer;

    // render_animation(create_scene_animation(), 1);
    const std::string path = "e:/temp/output/test.wif";

    auto scenes = pipeline::animation(0);

    pipeline::start(create_scene_animation()) >>
        pipeline::animation(1) >>
        pipeline::renderer(rendering::cartoon(BITMAP_SIZE, BITMAP_SIZE, samplers::grid(SAMPLES, SAMPLES), raytracers::v6(), loopers::multithreaded(4), 4, 0.005)) >>
        pipeline::wif(path);
}


int main()
{
    logging::configure();

    // TIMED_FUNC(timerObj);

    //using namespace imaging::bitmap_consumers;
    // demos::marble(pipeline::wif("e:/temp/output/test.wif"));

    render();
    // scripting::run_script("e:/repos/ucll/3dcg/raytracer2/scripts/test.chai");    
}

#endif
