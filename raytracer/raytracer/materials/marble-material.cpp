#include "materials/marble-material.h"
#include "math/functions/perlin.h"

using namespace raytracer;
using namespace imaging;
using namespace math;


Material raytracer::materials::marble2d()
{
    std::function<MaterialProperties(double)> converter = [](double t) -> MaterialProperties {
        MaterialProperties properties;
        properties.ambient = colors::black();
        properties.diffuse = t * colors::white();
        properties.specular = colors::black();
        properties.specular_exponent = 0.0;
        properties.reflectivity = 0.0;

        return properties;
    };

    return make_2d_material(math::functions::marble2d() >> from_lambda<MaterialProperties, double>(converter));
}