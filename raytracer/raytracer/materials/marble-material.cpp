#include "materials/marble-material.h"
#include "math/functions.h"

using namespace raytracer;
using namespace imaging;
using namespace math;


Material raytracer::materials::marble2d(unsigned octaves, double turbulence)
{
    std::function<MaterialProperties(double)> converter = [](double t) -> MaterialProperties {
        MaterialProperties properties = create_material_properties_with()
            .diffuse(t * colors::white())
            .specular(colors::white() * 0.5, 10.0)
            .reflectivity(0.3);

        return properties;
    };

    return make_2d_material(math::functions::marble2d(octaves, turbulence) >> from_lambda<MaterialProperties, double>(converter));
}

Material raytracer::materials::marble3d(unsigned octaves, double turbulence)
{
    std::function<MaterialProperties(double)> converter = [](double t) -> MaterialProperties {
        MaterialProperties properties = create_material_properties_with()
            .diffuse(t * colors::white());

        return properties;
    };

    return make_3d_material(math::functions::marble3d(octaves, turbulence) >> from_lambda<MaterialProperties, double>(converter));
}
