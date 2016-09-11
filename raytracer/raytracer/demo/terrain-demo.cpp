#include "demo/terrain-demo.h"
#include "materials/materials.h"
#include "cameras/cameras.h"
#include "imaging/wif-format.h"
#include "raytracers/ray-tracers.h"
#include "renderers/renderers.h"
#include "samplers/samplers.h"
#include "raytracers/scene.h"
#include "math/function.h"
#include "animation/animation.h"
#include "pipeline/pipelines.h"
#include "loopers/loopers.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;


namespace
{
    constexpr unsigned ANTIALIASING = 1;
    constexpr unsigned FPS = 1;
    constexpr unsigned HPIXELS = 500;
    constexpr unsigned VPIXELS = 500;
    constexpr unsigned N_THREADS = 4;

    raytracer::Primitive create_root(TimeStamp)
    {
        using namespace raytracer::primitives;
        using namespace raytracer::materials;

        MaterialProperties white(colors::white() * 0.1, colors::white() * 0.8, colors::black(), 0);
        auto material = uniform(white);

        return decorate(material, terrain());
    }

    std::vector<raytracer::LightSource> create_light_sources(TimeStamp)
    {
        using namespace raytracer::lights;

        std::vector<LightSource> light_sources;
        light_sources.push_back(lights::omnidirectional(Point3D(5, 2, 5), colors::white()));

        return light_sources;
    }

    raytracer::Camera create_camera(TimeStamp)
    {
        return raytracer::cameras::perspective(Point3D(0, 2, 0), Point3D(5, 0, 5), Vector3D(0, 1, 0), 1, 1);
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

        return make_animation<std::shared_ptr<Scene>>(function, Duration::from_seconds(1));
    }

    void render(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
    {
        auto scene_animation = create_scene_animation();
        auto ray_tracer = raytracer::raytracers::v6();

        auto sampler = raytracer::samplers::multi_jittered(ANTIALIASING);
        auto renderer = raytracer::renderers::standard(HPIXELS, VPIXELS, sampler, ray_tracer, loopers::smart_looper(N_THREADS));

        pipeline::start(create_scene_animation())
            >> pipeline::animation(FPS)
            >> pipeline::renderer(renderer)
            >> output;
    }
}

void demos::terrain(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    render(output);
}
