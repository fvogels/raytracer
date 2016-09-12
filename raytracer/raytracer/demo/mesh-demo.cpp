#include "demo/mesh-demo.h"
#include "demo/demo.h"
#include "util/lazy.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class MeshDemo : public Demo
    {
    public:
        MeshDemo(unsigned bitmap_size, animation::Duration duration, unsigned fps, unsigned antialias)
            : Demo(bitmap_size, duration, fps, antialias), m_mesh(raytracer::primitives::fast_mesh("E:/temp/lucy.bmesh"))
        {
            // NOP
        }

    protected:
        raytracer::Primitive create_root(TimeStamp now)
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            auto material = uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 10, 0.0, 0, 0));
            auto angle_animation = animation::animate(0_degrees, 360_degrees, 1_s);

            return decorate(material, rotate_around_y(angle_animation(now), rotate_around_x(-90_degrees, center(Point3D(0, 0, 0), m_mesh))));
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

    private:
        Primitive m_mesh;
    };
}

void demos::mesh(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    MeshDemo(500, 1_s, 30, 2);
}
