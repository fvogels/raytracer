#include "materials/perlin-material.h"
#include "math/functions.h"

using namespace raytracer;
using namespace imaging;
using namespace math;


Material raytracer::materials::perlin2d(unsigned seed, unsigned octaves, math::Function<MaterialProperties(double)> converter)
{
    return make_2d_material(math::functions::perlin<double, Point2D>(seed, octaves) >> converter);
}

Material raytracer::materials::perlin3d(unsigned seed, unsigned octaves, math::Function<MaterialProperties(double)> converter)
{
    return make_3d_material(math::functions::perlin<double, Point3D>(seed, octaves) >> converter);
}
