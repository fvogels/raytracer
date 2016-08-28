#include "demo/split-depth-demo.h"
#include "materials/materials.h"
#include "cameras/cameras.h"
#include "imaging/wif-format.h"
#include "raytracers/ray-tracers.h"
#include "rendering/renderers.h"
#include "sampling/samplers.h"
#include "raytracers/scene.h"
#include "math/function.h"
#include "animation/animations.h"
#include "pipeline/pipelines.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;


namespace
{
    constexpr unsigned ANTIALIASING = 2;
    constexpr unsigned FPS = 30;
    constexpr unsigned HPIXELS = 500;
    constexpr unsigned VPIXELS = 500;
    constexpr unsigned N_THREADS = 4;

    raytracer::Primitive create_root(TimeStamp now)
    {
        using namespace raytracer::primitives;
        using namespace raytracer::materials;

        auto anim = animation::circular(Point3D(0, 0, 2), Point3D(0, 0, 0), Vector3D(0, 1, 0), interval(0_degrees, 360_degrees), Duration::from_seconds(2));

        return decorate(uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.5, 0, 1.5)),
            translate(anim(now) - Point3D(0, 0, 0), sphere()));
    }

    std::vector<raytracer::LightSource> create_light_sources(TimeStamp)
    {
        using namespace raytracer::lights;

        std::vector<LightSource> light_sources;
        light_sources.push_back(omnidirectional(Point3D(5, 5, 5), colors::white()));

        return light_sources;
    }

    raytracer::Camera create_camera(TimeStamp)
    {
        return raytracer::cameras::perspective(Point3D(0, 0, 5), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
    }

    Animation<std::shared_ptr<Scene>> create_scene_animation()
    {
        std::function<std::shared_ptr<Scene>(TimeStamp)> lambda = [](TimeStamp now) {
            auto camera = create_camera(now);
            auto root = create_root(now);
            auto light_sources = create_light_sources(now);
            auto scene = std::make_shared<Scene>(camera, root, light_sources);

            return scene;
        };

        auto function = from_lambda(lambda);

        return make_animation<std::shared_ptr<Scene>>(function, Duration::from_seconds(2));
    }

    void render(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
    {
        auto scene_animation = create_scene_animation();
        auto ray_tracer = raytracer::raytracers::v6();
        auto renderer = raytracer::renderers::split_depth(HPIXELS, VPIXELS, raytracer::samplers::stratified_fixed(ANTIALIASING, ANTIALIASING), ray_tracer, util::loopers::looper(N_THREADS), 0.02, Point3D(0, 0, 5), Point3D(0, 0, 0));

        pipeline::start(create_scene_animation())
            >> pipeline::animation(FPS)
            >> pipeline::renderer(renderer)
            >> output;
    }
}

void demos::split_depth(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    render(output);
}
