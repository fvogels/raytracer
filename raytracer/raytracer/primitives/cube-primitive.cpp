#include "primitives/cube-primitive.h"
#include "primitives/box-primitive.h"
#include <assert.h>
#include <cmath>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


Primitive raytracer::primitives::cube(double size)
{
    return box(size, size, size);
}
