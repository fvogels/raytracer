#include "materials/wood-material.h"
#include "math/functions.h"

using namespace raytracer;
using namespace imaging;
using namespace math;


Material raytracer::materials::wood2d(unsigned octaves, double turbulence)
{
    std::function<MaterialProperties(double)> converter = [](double t) -> MaterialProperties {
        MaterialProperties properties(colors::black(), colors::red() * 0.5 * (1 - t), colors::black(), 0.0, 0.0, 0.0, 0.0);

        return properties;
    };

    return make_2d_material(math::functions::wood2d(octaves, turbulence) >> from_lambda<MaterialProperties, double>(converter));
}
