#include "demo/mesh-demo.h"
#include "materials/materials.h"
#include "cameras/cameras.h"
#include "imaging/wif-format.h"
#include "raytracers/ray-tracers.h"
#include "renderers/renderers.h"
#include "samplers/samplers.h"
#include "raytracers/scene.h"
#include "math/function.h"
#include "animation/animation.h"
#include "animation/interval-animation.h"
#include "pipeline/pipelines.h"
#include "loopers/loopers.h"
#include "util/lazy.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;


namespace
{
    constexpr unsigned ANTIALIASING = 2;
    constexpr unsigned FPS = 30;
    constexpr unsigned HPIXELS = 1000;
    constexpr unsigned VPIXELS = 1000;
    constexpr unsigned N_THREADS = 4;

    Lazy<Primitive> mesh([]() -> Primitive {
        return raytracer::primitives::fast_mesh("E:/temp/lucy.bmesh");
    });

    raytracer::Primitive create_root(TimeStamp now)
    {
        using namespace raytracer::primitives;
        using namespace raytracer::materials;

        auto material = uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 10, 0.0, 0, 0));
        auto angle_animation = animation::animate(0_degrees, 360_degrees, 1_s);

        return decorate(material, rotate_around_y(angle_animation(now), rotate_around_x(-90_degrees, center(Point3D(0, 0, 0), mesh.value()))));
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
        return raytracer::cameras::perspective(Point3D(0, 0, 3), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
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
        auto renderer = raytracer::renderers::standard(HPIXELS, VPIXELS, raytracer::samplers::multi_jittered(ANTIALIASING), ray_tracer, loopers::smart_looper(N_THREADS));

        pipeline::start(create_scene_animation())
            >> pipeline::animation(FPS)
            >> pipeline::renderer(renderer)
            >> output;
    }
}

void demos::mesh(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    render(output);
}
