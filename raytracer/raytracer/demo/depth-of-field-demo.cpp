#include "demo/depth-of-field-demo.h"
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
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;


namespace
{
    constexpr unsigned ANTIALIASING = 1;
    constexpr unsigned FPS = 30;
    constexpr unsigned HPIXELS = 500;
    constexpr unsigned VPIXELS = 500;

    raytracer::Primitive create_root(TimeStamp now)
    {
        using namespace raytracer::primitives;
        using namespace raytracer::materials;

        std::vector<Primitive> spheres;
        for (double z = 0; z <= 24; z += 3)
        {
            spheres.push_back(translate(vector(2, 0, z), sphere()));
            spheres.push_back(translate(vector(-2, 0, z), sphere()));
        }

        auto sphere_union = primitives::accelerated_union(spheres);

        MaterialProperties material_properties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.2, 0, 0);
        return decorate(uniform(material_properties), sphere_union);
    }

    std::vector<raytracer::LightSource> create_light_sources(TimeStamp now)
    {
        using namespace raytracer::lights;

        std::vector<LightSource> light_sources;
        light_sources.push_back(omnidirectional(point(0, 5, 5), colors::white()));

        return light_sources;
    }

    raytracer::Camera create_camera(TimeStamp now)
    {
        return raytracer::cameras::depth_of_field_perspective(point(0, 0, 0), point(0, 0, 1 + now.seconds() * 6), vector(0, 1, 0), 1, 1, 0.05, samplers::grid(3, 3));
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

    void render(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>> output)
    {
        auto scene_animation = create_scene_animation();
        auto ray_tracer = raytracer::raytracers::v6();
        auto renderer = raytracer::rendering::standard_multithreaded(HPIXELS, VPIXELS, raytracer::samplers::grid(ANTIALIASING, ANTIALIASING), ray_tracer, 4);

        pipeline::start(create_scene_animation())
            >> pipeline::animation(FPS)
            >> pipeline::renderer(renderer)
            >> output;
    }
}

void demos::depth_of_field(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>> output)
{
    render(output);
}