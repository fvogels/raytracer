#include "demo/sphere-bumpifier-demo.h"
#include "math/functions.h"
#include "demo/demo.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    constexpr unsigned ANTIALIASING = 2;
    constexpr unsigned FPS = 10;
    constexpr unsigned HPIXELS = 500;
    constexpr unsigned VPIXELS = 500;
    constexpr unsigned N_THREADS = 4;

    class SphereBumpifierDemo : public Demo
    {
    public:
        using Demo::Demo;

    protected:
        raytracer::Primitive create_root(TimeStamp now) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            auto perlin = math::functions::perlin<Vector3D, Point3D>(1, 79516);
            std::function<Vector3D(const Point3D&)> bumpificator = [perlin, now](const Point3D& p) -> Vector3D {
                Point3D q(p.x() * 50, p.y() * 50, p.z() * 50);

                return perlin(q) * now.seconds() / 10.0;
            };

            // auto angle_animation = animation::animate(0_degrees, 90_degrees, 1_s);
            auto material = uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.5, 0, 1.5));

            return bumpify(from_lambda(bumpificator), decorate(material, sphere()));
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
    };
}

void demos::bumpify_sphere(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    SphereBumpifierDemo(500, 1_s, 30, 1).render(output);
}
