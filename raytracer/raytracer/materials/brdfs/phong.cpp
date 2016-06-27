#include "materials/brdfs/phong.h"
#include "materials/brdfs/diffuse-component.h"
#include "materials/brdfs/specular-component.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace raytracer::brdfs;
using namespace imaging;


BRDF raytracer::brdfs::phong(const color& diffuse, const color& specular)
{
    return diffuse_component(diffuse) + specular_component(specular);
}