#include "materials/brdfs/phong.h"
#include "materials/brdfs/diffuse-component.h"
#include "materials/brdfs/specular-component.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace raytracer::brdfs;
using namespace imaging;


BRDF raytracer::brdfs::phong(const Color& diffuse_color, const Color& specular_color, double specular_exponent)
{
    return diffuse_component(diffuse_color) + specular_component(specular_color, specular_exponent);
}