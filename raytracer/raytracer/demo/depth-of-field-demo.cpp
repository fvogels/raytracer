#include "demo/depth-of-field-demo.h"
#include "materials/materials.h"
#include "cameras/cameras.h"
#include "imaging/wif-format.h"
#include "raytracing/ray-tracers.h"
#include "rendering/renderers.h"
#include "sampling/samplers.h"
#include "raytracing/scene.h"
#include "math/function.h"
#include "animation/animations.h"
#include "pipeline/pipelines.h"
#include "easylogging++.h"

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

    raytracer::Primitive create_root(TimeStamp)
    {
        using namespace raytracer::primitives;
        using namespace raytracer::materials;

        std::vector<Primitive> spheres;
        for (double z = 0; z <= 24; z += 3)
        {
            spheres.push_back(translate(Vector3D(2, 0, z), sphere()));
            spheres.push_back(translate(Vector3D(-2, 0, z), sphere()));
        }
        auto sphere_union = primitives::accelerated_union(spheres);

        MaterialProperties material_properties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.2, 0, 0);
        auto decorated_spheres = decorate(uniform(material_properties), sphere_union);

        MaterialProperties white(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.5, 0, 0);
        MaterialProperties black(colors::black() * 0.1, colors::black() * 0.8, colors::white(), 20, 0.5, 0, 0);
        auto plane = decorate(checkered(uniform(white), uniform(black)),
            translate(Vector3D(0, -1, 0), xz_plane()));

        std::vector<Primitive> children = { plane, decorated_spheres };
        return make_union( children );
    }

    std::vector<raytracer::LightSource> create_light_sources(TimeStamp)
    {
        using namespace raytracer::lights;

        std::vector<LightSource> light_sources;
        light_sources.push_back(omnidirectional(Point3D(0, 5, 5), colors::white()));

        return light_sources;
    }

    raytracer::Camera create_camera(TimeStamp now)
    {
        auto sampler = samplers::multi_jittered(3);

        auto lookat_animation = animation::interval(Point3D(0, 0, 1), Point3D(0, 0, 7), Duration::from_seconds(1));

        return raytracer::cameras::depth_of_field_perspective(Point3D(0, 0, 0), lookat_animation(now), Vector3D(0, 1, 0), 1, 1, 0.05, sampler);
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

        return make_animation<std::shared_ptr<Scene>>(function, Duration::from_seconds(3));
    }

    void render(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>> output)
    {
        auto scene_animation = create_scene_animation();
        auto ray_tracer = raytracer::raytracers::v6();
        auto sampler = raytracer::samplers::multi_jittered(ANTIALIASING);
        auto renderer = raytracer::renderers::standard(HPIXELS, VPIXELS, sampler, ray_tracer, util::loopers::looper(N_THREADS));

        pipeline::start(create_scene_animation())
            >> pipeline::animation(30)
            >> pipeline::renderer(renderer)
            >> output;
    }
}

void demos::depth_of_field(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>> output)
{
    render(output);
}
