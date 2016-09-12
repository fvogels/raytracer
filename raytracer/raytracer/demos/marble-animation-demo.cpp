#include "demos/marble-animation-demo.h"
#include "demos/demo.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class MarbleDemo : public Demo
    {
    public:
        using Demo::Demo;

    protected:
        raytracer::Primitive create_root(TimeStamp now) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            return decorate(to_animated_2d_material(marble3d(4, 2))(now), xy_plane());
        }

        std::vector<raytracer::LightSource> create_light_sources(TimeStamp) override
        {
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;
            light_sources.push_back(directional(Vector3D(0, 0, -1), colors::white()));

            return light_sources;
        }

        raytracer::Camera create_camera(TimeStamp) override
        {
            return raytracer::cameras::perspective(Point3D(0, 0, 10), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
        }        
    };
}

void demos::marble(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    MarbleDemo(500, 1_s, 30, 2).render(output);
}
