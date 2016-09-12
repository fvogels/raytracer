#include "demo/terrain-demo.h"
#include "materials/materials.h"
#include "cameras/cameras.h"
#include "imaging/wif-format.h"
#include "raytracers/ray-tracers.h"
#include "renderers/renderers.h"
#include "samplers/samplers.h"
#include "raytracers/scene.h"
#include "math/functions.h"
#include "animation/animation.h"
#include "pipeline/pipelines.h"
#include "loopers/loopers.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;


namespace
{
    constexpr unsigned ANTIALIASING = 2;
    constexpr unsigned FPS = 1;
    constexpr unsigned HPIXELS = 500;
    constexpr unsigned VPIXELS = 500;
    constexpr unsigned N_THREADS = 4;

    raytracer::Primitive create_root(TimeStamp)
    {
        using namespace raytracer::primitives;
        using namespace raytracer::materials;

        MaterialProperties terrain_material_properties(colors::white() * 0.1, colors::green() * 0.8, colors::black(), 0);
        MaterialProperties water_material_properties(colors::white() * 0.1, colors::blue() * 0.8, colors::white() * 0.2, 10, 0.5);
        auto terrain_material = uniform(terrain_material_properties);
        auto water_material = uniform(water_material_properties);
        auto landscape = decorate(terrain_material, terrain());

        auto water_perlin = math::functions::perlin<Vector3D, Point3D>(1, 38931);
        std::function<Vector3D(const Point3D&)> lambda = [water_perlin](const Point3D& p) -> Vector3D {
            return water_perlin(p * 10) * 0.01;
        };
        math::Function<Vector3D(const Point3D&)> water_bumps = from_lambda(lambda);

        auto sea_level = landscape->bounding_box().y().from_relative(0.40);
        auto water = decorate(water_material, crop_by_box(translate(Vector3D(0, sea_level, 0), bumpify(water_bumps, xz_plane())), landscape->bounding_box()));

        std::vector<Primitive> primitives = { landscape, water };

        return make_union(primitives);
    }

    std::vector<raytracer::LightSource> create_light_sources(TimeStamp)
    {
        using namespace raytracer::lights;

        std::vector<LightSource> light_sources;
        light_sources.push_back(lights::omnidirectional(Point3D(5, 8, 5), colors::white()));

        return light_sources;
    }

    raytracer::Camera create_camera(TimeStamp)
    {
        return raytracer::cameras::perspective(Point3D(-2, 10, -2), Point3D(10, 0, 10), Vector3D(0, 1, 0), 1, 1);
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
