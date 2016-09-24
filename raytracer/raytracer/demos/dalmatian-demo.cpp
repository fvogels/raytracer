#include "demos/dalmatian-demo.h"
#include "demos/demo.h"
#include "util/lazy.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class Dalmatian2DDemo : public Demo
    {
    public:
        Dalmatian2DDemo(unsigned bitmap_size, animation::Duration duration, unsigned fps, unsigned antialias)
            : Demo(bitmap_size, duration, fps, antialias)
        {
            // NOP
        }

    protected:
        raytracer::Primitive create_root(TimeStamp) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            MaterialProperties black_material_properties(colors::white() * 0.1, colors::white() * 0.8, colors::black(), 0);
            MaterialProperties white_material_properties(colors::white() * 0.1, colors::black(), colors::black(), 0);
            Material black_material = uniform(white_material_properties);
            Material white_material = uniform(black_material_properties);
            Material material = scale(0.05, 0.1, dalmatian2d(10, black_material, white_material));

            Primitive primitive = decorate(material, sphere());

            return primitive;
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
            return raytracer::cameras::perspective(Point3D(0, 0, 3), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
        }
    };

    class Dalmatian3DDemo : public Demo
    {
    public:
        Dalmatian3DDemo(unsigned bitmap_size, animation::Duration duration, unsigned fps, unsigned antialias)
            : Demo(bitmap_size, duration, fps, antialias)
        {
            // NOP
        }

    protected:
        raytracer::Primitive create_root(TimeStamp) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            MaterialProperties black_material_properties(colors::white() * 0.1, colors::white() * 0.8, colors::black(), 0);
            MaterialProperties white_material_properties(colors::white() * 0.1, colors::black(), colors::black(), 0);
            Material black_material = uniform(white_material_properties);
            Material white_material = uniform(black_material_properties);
            Material material = scale(0.25, 0.25, 0.25, dalmatian3d(10, black_material, white_material));

            Primitive primitive = decorate(material, sphere());

            return primitive;
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
            return raytracer::cameras::perspective(Point3D(0, 0, 3), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
        }
    };
}

void demos::dalmatian2d(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    Dalmatian2DDemo(500, 1_s, 1, 2).render(output);
}

void demos::dalmatian3d(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    Dalmatian3DDemo(500, 1_s, 1, 2).render(output);
}