#include "demos/terrain-demo.h"
#include "demos/demo.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class TerrainDemo : public Demo
    {
    public:
        using Demo::Demo;

    protected:
        raytracer::Primitive create_root(TimeStamp) override
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            MaterialProperties terrain_material_properties(colors::white() * 0.1, colors::green() * 0.8, colors::black(), 0);
            MaterialProperties water_material_properties(colors::white() * 0.1, colors::blue() * 0.8, colors::white() * 0.2, 10, 0.5);
            auto terrain_material = uniform(terrain_material_properties);
            auto water_material = uniform(water_material_properties);
            auto landscape = decorate(terrain_material, terrain());

            auto sea_level = landscape->bounding_box().y().from_relative(0.40);
            auto water = decorate(water_material, crop_by_box(translate(Vector3D(0, sea_level, 0), xz_plane()), landscape->bounding_box()));

            std::vector<Primitive> primitives = { landscape, water };

            return make_union(primitives);
        }

        std::vector<raytracer::LightSource> create_light_sources(TimeStamp) override
        {
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;
            light_sources.push_back(lights::omnidirectional(Point3D(5, 8, 5), colors::white()));

            return light_sources;
        }

        raytracer::Camera create_camera(TimeStamp) override
        {
            return raytracer::cameras::perspective(Point3D(-2, 10, -2), Point3D(10, 0, 10), Vector3D(0, 1, 0), 1, 1);
        }
    };
}

void demos::terrain(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    TerrainDemo(500, 1_s, 1, 2).render(output);
}
