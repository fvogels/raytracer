#ifndef TEST_BUILD

#define COULD_BE_UNUSED(X) (void)(X)

#include "imaging/bitmap.h"
#include "imaging/wif-format.h"
#include "primitives/primitives.h"
#include "cameras/cameras.h"
#include "math/rasterizer.h"
#include "math/functions.h"
#include "math/functions/noise.h"
#include "sampling/samplers.h"
#include "materials/materials.h"
#include "lights/lights.h"
#include "raytracing/ray-tracers.h"
#include "rendering/renderers.h"
#include "rendering/cartoon-renderer.h"
#include "animation/animations.h"
#include "demo/demos.h"
#include "logging.h"
#include "util/lazy.h"
#include "math/point.h"
#include "imaging/bitmap-function.h"
#include "pipeline/pipelines.h"
#include "util/misc.h"
#include "util/looper.h"
#include "util/beep.h"
#include "scripting/scripting.h"
#include "easylogging++.h"
#include "version.h"
#include <assert.h>
#include <type_traits>
#include <list>

#ifdef NDEBUG
const int BITMAP_SIZE = 500;
const int SAMPLES = 2;
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


Primitive load_mesh(const std::string& path)
{
    std::ifstream in(path);
    return raytracer::primitives::fast_mesh_bin(in);
}

Lazy<raytracer::Primitive> bunny([]() {
    return load_mesh("e:/temp/bunny.bmesh");
});
Lazy<raytracer::Primitive> buddha([]() {
    return load_mesh("e:/temp/buddha.bmesh");
});
Lazy<raytracer::Primitive> dragon([]() {
    return load_mesh("e:/temp/dragon.bmesh");
});
Lazy<raytracer::Primitive> statuette([]() {
    return load_mesh("e:/temp/statuette.bmesh");
});
Lazy<raytracer::Primitive> lucy([]() {
    return load_mesh("e:/temp/lucy.bmesh");
});

raytracer::Primitive create_root(TimeStamp now)
{
    COULD_BE_UNUSED(now);

    using namespace raytracer::primitives;
    using namespace raytracer::materials;

    std::vector<Primitive> primitives;

    auto front = translate(Vector3D(0, 0, 4.75), scale(5, 5, 5, sphere()));
    auto back = translate(Vector3D(0, 0, -4.75), scale(5, 5, 5, sphere()));
    auto lens_material = uniform(MaterialProperties(colors::white() * 0.1, colors::red() * 0.2, colors::white(), 20, 0, 0.8, 1 + now.seconds()));
    auto lens = decorate(lens_material, intersection(front, back));


    auto obj_material = texture("e:/temp/earth2.bmp");
    // auto obj_position = animation::straight(Vector3D(4, 0, -3), Vector3D(-4, 0, -3), Duration::from_seconds(1))(now);
    auto obj_position = Vector3D(0, 0, -3);
    auto obj = decorate(obj_material, translate(obj_position, rotate_around_y(360_degrees * now.seconds(), sphere())));

    std::vector<Primitive> children = { lens, obj };
    return make_union(children);
}

std::vector<raytracer::LightSource> create_light_sources(TimeStamp now)
{
    COULD_BE_UNUSED(now);

    using namespace raytracer::lights;

    std::vector<LightSource> light_sources;

    Point3D light_position(0, 5, 2);
    light_sources.push_back(omnidirectional(light_position, colors::white()));
    // light_sources.push_back(spot(light_position, Point3D(0, 0, 0), 120_degrees, colors::white()));
    // light_sources.push_back(directional(Vector3D(0, -0.1, 1).normalized(), colors::white()));
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
    COULD_BE_UNUSED(now);

    using namespace math::functions::easing;

    // auto camera_position_animation = circular(Point3D(0, 1, 5), Point3D(0, 0, 0), Vector3D::y_axis(), Interval<Angle>(0_degrees, 360_degrees), 1_s);

    auto camera_position_animation = circular(Point3D(0, 0, 3), Point3D(0, 0, 0), Vector3D(0, 1, 0).normalized(), math::Interval<Angle>(0_degrees, 360_degrees), Duration::from_seconds(1));
    Point3D camera_position = Point3D(0, 0, 5);
    // Point3D camera_position = camera_position_animation(now);
    Vector3D up(0, 1, 0);
    auto camera = raytracer::cameras::perspective(camera_position, Point3D(0, 0, 0), up, 1, 1);
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

    pipeline::start(create_scene_animation()) >>
        pipeline::animation(30) >>
        pipeline::renderer(renderers::standard(BITMAP_SIZE, BITMAP_SIZE, samplers::stratified_fixed(SAMPLES, SAMPLES), raytracers::v6(), loopers::multithreaded(4))) >>
        pipeline::wif(path);
}

void process_command_line_arguments(int argc, char** argv)
{
    int i = 1;

    while (i < argc)
    {
        std::string current = argv[i];

        if (starts_with("-s", current))
        {
            std::string path = current.substr(2);

            LOG(INFO) << "Rendering " << path;
            TIMED_SCOPE(timer, "Rendering " + path);

#ifdef EXCLUDE_SCRIPTING
            abort("Cannot run script - scripting was excluded");
#else
            scripting::run_script(path);
#endif
        }
        else if (current == "--quiet")
        {
            logging::quiet();
        }
        else if (current == "--version")
        {
            std::cerr << "Build " << BUILD_NUMBER << std::endl;
        }
        else if (current == "--beep")
        {
            beep();
        }
        else
        {
            std::cerr << "Unknown flag " << current << std::endl;
            abort();
        }

        ++i;
    }
}

int main(int argc, char** argv)
{    
    logging::configure();

    process_command_line_arguments(argc, argv);

    // demos::bumpify_plane(pipeline::wif("e:/temp/output/test.wif"));

    // render();
    // scripting::run_script("e:/repos/ucll/3dcg/raytracer2/scripts/test.chai");    

    
}

#endif
