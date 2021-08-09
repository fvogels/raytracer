#include "demos/cartoon-renderer-demo.h"
#include "demos/demo.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class CartoonRendererDemo : public Demo
    {
    public:
        using Demo::Demo;

    protected:
        raytracer::Primitive create_root(TimeStamp now) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            MaterialProperties plane_material_properties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 5);
            Material plane_material = uniform(plane_material_properties);

            MaterialProperties red_material_properties(colors::white() * 0.1, colors::red() * 0.8, colors::white(), 5);
            MaterialProperties green_material_properties(colors::white() * 0.1, colors::green() * 0.8, colors::white(), 5);
            MaterialProperties blue_material_properties(colors::white() * 0.1, colors::blue() * 0.8, colors::white(), 5);
            Material red_material = uniform(red_material_properties);
            Material green_material = uniform(green_material_properties);
            Material blue_material = uniform(blue_material_properties);

            auto sphere1 = decorate(red_material, group(1, translate(Vector3D::cylindrical_z(2, 30_degrees, 0), sphere())));
            auto sphere2 = decorate(green_material, group(1, translate(Vector3D::cylindrical_z(2, 150_degrees, 0), sphere())));
            auto sphere3 = decorate(blue_material, group(1, translate(Vector3D::cylindrical_z(2, 270_degrees, 0), sphere())));
            auto plane = decorate(plane_material, translate(Vector3D(0, 0, -5), xy_plane()));

            std::vector<Primitive> spheres_list = { sphere1, sphere2, sphere3 };
            Primitive spheres = accelerated_union(spheres_list);

            auto angle_animation = animation::animate(0_degrees, 360_degrees, 5_s);

            std::vector<Primitive> primitives = { rotate_around_z(angle_animation(now), spheres), plane };
            return make_union(primitives);
        }

        std::vector<raytracer::LightSource> create_light_sources(TimeStamp) override
        {
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;
            light_sources.push_back(omnidirectional(Point3D(0, 0, 5), colors::white()));

            return light_sources;
        }

        raytracer::Camera create_camera(TimeStamp) override
        {
            auto sampler = samplers::multi_jittered(3);

            return raytracer::cameras::perspective(Point3D(0, 0, 8), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
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

            return make_animation<std::shared_ptr<Scene>>(function, m_duration);
        }

        Renderer create_renderer() override
        {
            return raytracer::renderers::cartoon(m_bitmap_size, m_bitmap_size, create_sampler(), create_ray_tracer(), create_scheduler(), 4);
        }
    };
}

void demos::cartoon_renderer(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>> output)
{
    CartoonRendererDemo(500, 5_s, 30, 2).render(output);
}
