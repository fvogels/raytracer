#include "demo/depth-of-field-demo.h"
#include "demo/demo.h"
#include "loopers/loopers.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class DepthOfFieldDemo : public Demo
    {
    public:
        using Demo::Demo;

    protected:
        raytracer::Primitive create_root(TimeStamp) override
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
            return make_union(children);
        }

        std::vector<raytracer::LightSource> create_light_sources(TimeStamp) override
        {
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;
            light_sources.push_back(omnidirectional(Point3D(0, 5, 5), colors::white()));

            return light_sources;
        }

        raytracer::Camera create_camera(TimeStamp now) override
        {
            auto sampler = samplers::multi_jittered(3);

            auto lookat_animation = animation::animate(Point3D(0, 0, 1), Point3D(0, 0, 7), Duration::from_seconds(1));

            return raytracer::cameras::depth_of_field_perspective(Point3D(0, 0, 0), lookat_animation(now), Vector3D(0, 1, 0), 1, 1, 0.05, sampler);
        }

        Animation<std::shared_ptr<Scene>> create_scene_animation() override
        {
            std::function<std::shared_ptr<Scene>(TimeStamp)> lambda = [this](TimeStamp now) {
                auto camera = create_camera(now);
                auto root = create_root(now);
                auto light_sources = create_light_sources(now);
                auto scene = std::make_shared<Scene>(camera, root, light_sources);

                return scene;
            };

            auto function = from_lambda(lambda);

            return make_animation<std::shared_ptr<Scene>>(function, Duration::from_seconds(3));
        }

    public:
        void render(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>> output) override
        {
            auto scene_animation = create_scene_animation();
            auto ray_tracer = raytracer::raytracers::v6();
            auto sampler = raytracer::samplers::multi_jittered(m_antialias);
            auto renderer = raytracer::renderers::standard(m_bitmap_size, m_bitmap_size, sampler, ray_tracer, loopers::smart_looper(4));

            pipeline::start(create_scene_animation())
                >> pipeline::animation(m_fps)
                >> pipeline::renderer(renderer)
                >> output;
        }
    };
}

void demos::depth_of_field(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>> output)
{
    DepthOfFieldDemo(500, 3_s, 30, 2).render(output);
}
