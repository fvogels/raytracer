#include "demos/split-depth-demo.h"
#include "demos/demo.h"
#include "loopers/loopers.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class SplitDepthDemo : public Demo
    {
    public:
        using Demo::Demo;

    protected:
        raytracer::Primitive create_root(TimeStamp now) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            auto anim = animation::circular(Point3D(0, 0, 2), Point3D(0, 0, 0), Vector3D(0, 1, 0), interval(0_degrees, 360_degrees), Duration::from_seconds(2));

            return decorate(uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.5, 0, 1.5)),
                translate(anim(now) - Point3D(0, 0, 0), sphere()));
        }

        std::vector<raytracer::LightSource> create_light_sources(TimeStamp) override
        {
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;
            light_sources.push_back(omnidirectional(Point3D(5, 5, 5), colors::white()));

            return light_sources;
        }

        raytracer::Camera create_camera(TimeStamp) override
        {
            return raytracer::cameras::perspective(Point3D(0, 0, 5), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
        }

        raytracer::Renderer create_renderer() override
        {
            return raytracer::renderers::split_depth(m_bitmap_size, m_bitmap_size, raytracer::samplers::multi_jittered(m_antialias), create_ray_tracer(), loopers::smart_looper(4), 0.02, Point3D(0, 0, 5), Point3D(0, 0, 0));
        }
    };

    
}

void demos::split_depth(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    SplitDepthDemo(500, 2_s, 30, 2).render(output);
}
