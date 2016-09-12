#include "demo/sampler-demo.h"
#include "demo/demo.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class SamplerDemo : public Demo
    {
    public:
        using Demo::Demo;

    protected:
        raytracer::Primitive create_root(TimeStamp) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            MaterialProperties white(colors::white() * 0.1, colors::white() * 0.8, colors::black(), 0, 0, 0, 0);
            MaterialProperties black(colors::black() * 0.1, colors::black() * 0.8, colors::black(), 0, 0, 0, 0);
            auto material = checkered(uniform(white), uniform(black));

            return decorate(material, xz_plane());
        }

        std::vector<raytracer::LightSource> create_light_sources(TimeStamp) override
        {
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;
            light_sources.push_back(lights::directional(Vector3D(0, -1, 0), colors::white()));

            return light_sources;
        }

        raytracer::Camera create_camera(TimeStamp) override
        {
            return raytracer::cameras::perspective(Point3D(5, 1, 5), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
        }
    };
}

void demos::samplers(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    SamplerDemo(500, 1_s, 30, 2).render(output);
}
