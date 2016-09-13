#include "demos/fisheye-demo.h"
#include "demos/demo.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class FisheyeDemo : public Demo
    {
    public:
        using Demo::Demo;

    protected:
        raytracer::Primitive create_root(TimeStamp) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            std::vector<Primitive> sphere_list;
            for (double z = 0; z <= 24; z += 3)
            {
                sphere_list.push_back(translate(Vector3D(2, 0, -z), sphere()));
                sphere_list.push_back(translate(Vector3D(-2, 0, -z), sphere()));
            }

            MaterialProperties sphere_material_properties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.2, 0, 0);
            Material sphere_material = uniform(sphere_material_properties);
            auto spheres = decorate(sphere_material, accelerated_mesh(sphere_list));

            auto white = uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 10, 0.5, 0, 0));
            auto black = uniform(MaterialProperties(colors::black() * 0.1, colors::black() * 0.8, colors::white(), 10, 0.5, 0, 0));
            auto plane_material = checkered(white, black);
            auto plane = decorate(plane_material, translate(Vector3D(0, -1, 0), xz_plane()));

            std::vector<Primitive> primitives{ spheres, plane };
            return make_union(primitives);
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
            auto angle_animation = animation::animate(90_degrees, 270_degrees, 1_s);

            return raytracer::cameras::fisheye(Point3D(0, 0, 5), Point3D(0, 0, 0), Vector3D(0, 1, 0), 90_degrees + 180_degrees * now.seconds(), 180_degrees);
        }        
    };
}

void demos::fisheye(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    FisheyeDemo(500, 1_s, 30, 2).render(output);
}
