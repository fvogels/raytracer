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
#include "raytracers/ray-tracers.h"
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
#include "command-line-processor.h"
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

    primitives.push_back(translate(Vector3D(0, 5, 0), sphere()));
    primitives.push_back(cylinder_along_x());


    return decorate(white, make_union(primitives));
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

    Point3D camera_position = Point3D(20, 20, 20);
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

    return make_animation<std::shared_ptr<Scene>>(from_lambda<std::shared_ptr<Scene>, TimeStamp>(lambda), Duration::from_seconds(1));
}

void render()
{
    using namespace raytracer;

    // render_animation(create_scene_animation(), 1);
    const std::string path = "e:/temp/output/test.wif";

    pipeline::start(create_scene_animation()) >>
        pipeline::animation(1) >>
        pipeline::renderer(renderers::standard(BITMAP_SIZE, BITMAP_SIZE, samplers::stratified_fixed(SAMPLES, SAMPLES), raytracers::v6(), loopers::multithreaded(4))) >>
        pipeline::wif(path);
}

namespace
{
    // Note: these are not used anywhere for now
    std::map<std::string, std::string> external_variables;

    void render_script(const std::string& filename)
    {
        LOG(INFO) << "Rendering " << filename;
        TIMED_SCOPE(timer, "Rendering " + filename);

#       ifdef EXCLUDE_SCRIPTING
        LOG(ERROR) << "Cannot run script - scripting was excluded";
        abort();
#       else
        raytracer::scripting::run_script(filename);
#       endif
    }

    void quiet(const std::string&)
    {
        logging::quiet();
    }

    void show_version(const std::string&)
    {
        LOG(INFO) << "Build " << BUILD_NUMBER << std::endl;
    }

    void emit_beep(const std::string&)
    {
        ::beep();
    }

    void define_external_variable(const std::string& string)
    {
        auto equal_sign_location = string.find('=');

        if (equal_sign_location == std::string::npos)
        {
            LOG(ERROR) << "Invalid variable definition:" << string;
            abort();
        }
        else
        {
            std::string variable_name = string.substr(0, equal_sign_location);
            std::string variable_value = string.substr(equal_sign_location + 1);

            external_variables[variable_name] = variable_value;
        }
    }
}

void process_command_line_arguments(int argc, char** argv)
{
    CommandLineProcessor processor;

    processor.register_processor("-s", render_script);
    processor.register_processor("--quiet", quiet);
    processor.register_processor("--version", show_version);
    processor.register_processor("--beep", emit_beep);
    processor.register_processor("-d", define_external_variable);

    processor.process(argc, argv);

    LOG(INFO) << "Terminated successfully";
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
