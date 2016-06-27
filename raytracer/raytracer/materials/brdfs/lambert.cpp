#include "materials/brdfs/lambert.h"
#include "materials/brdfs/diffuse-component.h"
#include <algorithm>
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace raytracer::brdfs;
using namespace imaging;


BRDF raytracer::brdfs::lambert(const color& c)
{
    return diffuse_component(c);
}