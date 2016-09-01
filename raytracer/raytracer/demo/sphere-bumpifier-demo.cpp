#include "demo/sphere-bumpifier-demo.h"
#include "materials/materials.h"
#include "cameras/cameras.h"
#include "imaging/wif-format.h"
#include "raytracers/ray-tracers.h"
#include "renderers/renderers.h"
#include "samplers/samplers.h"
#include "raytracers/scene.h"
#include "math/functions.h"
#include "animation/animations.h"
#include "pipeline/pipelines.h"
#include "loopers/loopers.h"

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

        auto perlin = math::functions::perlin<double, Point3D>(4, 78);
        std::function<Vector3D(const Point3D&)> bumpificator = [perlin, now](const Point3D& p) -> Vector3D {
            Point3D q(p.x() * 10, p.y() * 10, p.z() * 10);
            double x = perlin(q);
            double y = perlin(q + Vector3D(100, 100, 100));
            double z = perlin(q - Vector3D(100, 100, 100));

            return Vector3D(x, y, z) * 0.1;
        };

        auto angle_animation = animation::animate(0_degrees, 90_degrees, 1_s);

        return bumpify(from_lambda(bumpificator), decorate(uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.5, 0, 1.5)),
            rotate_around_y(angle_animation(now), sphere())));
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

        return make_animation<std::shared_ptr<Scene>>(function, Duration::from_seconds(1));
    }

    void render(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
    {
        auto scene_animation = create_scene_animation();
        auto ray_tracer = raytracer::raytracers::v6();
        auto renderer = raytracer::renderers::standard(HPIXELS, VPIXELS, raytracer::samplers::stratified_fixed(ANTIALIASING, ANTIALIASING), ray_tracer, loopers::smart_looper(N_THREADS));

        pipeline::start(create_scene_animation())
            >> pipeline::animation(FPS)
            >> pipeline::renderer(renderer)
            >> output;
    }
}

void demos::bumpify_sphere(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    render(output);
}
