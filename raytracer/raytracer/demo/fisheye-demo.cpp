#include "demo/fisheye-demo.h"
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

        std::vector<Primitive> primitives;
        for (double z = 0; z <= 24; z += 3)
        {
            primitives.push_back(translate(Vector3D(2, 0, -z), sphere()));
            primitives.push_back(translate(Vector3D(-2, 0, -z), sphere()));
        }

        auto white = uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 10, 0.5, 0, 0));
        auto black = uniform(MaterialProperties(colors::black() * 0.1, colors::black() * 0.8, colors::white(), 10, 0.5, 0, 0));
        auto plane_material = checkered(white, black);
        auto plane = decorate(plane_material, translate(Vector3D(0, -1, 0), xz_plane()));
        primitives.push_back(plane);

        auto primitive_union = primitives::accelerated_union(primitives);

        MaterialProperties material_properties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.2, 0, 0);
        return decorate(uniform(material_properties), primitive_union);
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
        auto angle_animation = animation::animate(90_degrees, 270_degrees, 1_s);

        return raytracer::cameras::fisheye(Point3D(0, 0, 5), Point3D(0, 0, 0), Vector3D(0, 1, 0), 90_degrees + 180_degrees * now.seconds(), 180_degrees);
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
        auto renderer = raytracer::renderers::standard(HPIXELS, VPIXELS, raytracer::samplers::stratified_fixed(ANTIALIASING, ANTIALIASING), ray_tracer, util::loopers::looper(N_THREADS));

        pipeline::start(create_scene_animation())
            >> pipeline::animation(FPS)
            >> pipeline::renderer(renderer)
            >> output;
    }
}

void demos::fisheye(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    render(output);
}
