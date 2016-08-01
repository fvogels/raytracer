#include "demo/sampler-demo.h"
#include "materials/materials.h"
#include "cameras/cameras.h"
#include "imaging/wif-format.h"
#include "raytracing/ray-tracers.h"
#include "rendering/renderers.h"
#include "sampling/samplers.h"
#include "raytracing/scene.h"
#include "math/function.h"
#include "animation/animation.h"
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

        MaterialProperties white(colors::white() * 0.1, colors::white() * 0.8, colors::black(), 0, 0, 0, 0);
        MaterialProperties black(colors::black() * 0.1, colors::black() * 0.8, colors::black(), 0, 0, 0, 0);
        auto material = checkered(uniform(white), uniform(black));

        return decorate(material, xz_plane());
    }

    std::vector<raytracer::LightSource> create_light_sources(TimeStamp now)
    {
        using namespace raytracer::lights;

        std::vector<LightSource> light_sources;
        light_sources.push_back(lights::directional(Vector3D(0, -1, 0), colors::white()));

        return light_sources;
    }

    raytracer::Camera create_camera(TimeStamp now)
    {
        return raytracer::cameras::perspective(point(5, 1, 5), point(0, 0, 0), vector(0, 1, 0), 1, 1);
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
        // auto sampler = raytracer::samplers::single();
        auto sampler = raytracer::samplers::stratified_fixed(2, 2);
        // auto sampler = raytracer::samplers::random(4);
        auto renderer = raytracer::rendering::standard(HPIXELS, VPIXELS, sampler, ray_tracer, util::loopers::looper(N_THREADS));

        pipeline::start(create_scene_animation())
            >> pipeline::animation(1)
            >> pipeline::renderer(renderer)
            >> output;
    }
}

void demos::samplers(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    render(output);
}