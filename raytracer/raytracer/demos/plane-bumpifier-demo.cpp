#include "demos/plane-bumpifier-demo.h"
#include "math/functions.h"
#include "demos/demo.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class PlaneBumpifierDemo : public Demo
    {
    public:
        using Demo::Demo;

    protected:
        raytracer::Primitive create_root(TimeStamp now) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            auto perlin = math::functions::perlin<Vector3D, Point3D>(5, 4546);

            std::function<Vector3D(const Point2D& p)> lambda = [now, perlin](const Point2D& p) -> Vector3D {
                return perlin(Point3D(0.2 * p.x(), 0.2 * p.y(), now.seconds())) * 0.1;
            };
            auto bumpificator = from_lambda(lambda);
            // auto bumpificator = animation::xyz_to_xyt<Vector3D>(perlin)(now);

            return bumpify(bumpificator, decorate(uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 100, 0.5, 0, 0)), xz_plane()));
        }

        std::vector<raytracer::LightSource> create_light_sources(TimeStamp) override
        {
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;
            light_sources.push_back(directional(Vector3D(0, -0.1, 1).normalized(), colors::white()));

            return light_sources;
        }

        raytracer::Camera create_camera(TimeStamp) override
        {
            return raytracer::cameras::perspective(Point3D(0, 5, 5), Point3D(0, 0, -100), Vector3D(0, 1, 0), 1, 1);
        }
    };
}

void demos::bumpify_plane(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    PlaneBumpifierDemo(500, 1_s, 30, 2).render(output);
}
