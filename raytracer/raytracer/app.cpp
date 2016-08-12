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

    auto white = uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::black(), 0, 0, 0, 0));

    std::vector<Primitive> primitives;

    auto a = animation::ease(animation::interval(Point3D(0, 0, 0), Point3D(0, 1, 0), 1_s), functions::easing::easing_function<functions::easing::quadratic, functions::easing::in>());
    auto b = animation::interval(Point3D(0, 1, 0), Point3D(1, 1, 0), 1_s);

    auto s = translate(sequence(a,b)(now) - Point3D(0, 0, 0), decorate(white, sphere()));


    std::vector<Primitive> children = { s };
    return make_union(children);
}

std::vector<raytracer::LightSource> create_light_sources(TimeStamp now)
{
    COULD_BE_UNUSED(now);

    using namespace raytracer::lights;

    std::vector<LightSource> light_sources;

    Point3D light_position(0, 5, 5);
    light_sources.push_back(omnidirectional(light_position, colors::white()));

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

    Point3D camera_position = Point3D(0, 0, 5);
    auto camera = raytracer::cameras::perspective(camera_position, Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);

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

    return make_animation<std::shared_ptr<Scene>>(from_lambda<std::shared_ptr<Scene>, TimeStamp>(lambda), Duration::from_seconds(2));
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
            LOG(ERROR) << "Cannot run script - scripting was excluded";
            abort();
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
            LOG(INFO) << "Build " << BUILD_NUMBER << std::endl;
        }
        else if (current == "--beep")
        {
            beep();
        }
        else
        {
            LOG(ERROR) << "Unknown flag " << current << std::endl;
            abort();
        }

        ++i;
    }
}

int main(int argc, char** argv)
{    
    logging::configure();

    // process_command_line_arguments(argc, argv);

    // demos::bumpify_plane(pipeline::wif("e:/temp/output/test.wif"));

    render();
    // scripting::run_script("e:/repos/ucll/3dcg/raytracer2/scripts/test.chai");    

    
}

#endif
