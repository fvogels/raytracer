#include "primitives/square-primitive.h"
#include "primitives/rectangle-primitive.h"
#include "math/interval.h"
#include "math/misc.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


Primitive raytracer::primitives::xy_square(double size)
{
    return xy_rectangle(size, size);
}

Primitive raytracer::primitives::xz_square(double size)
{
    return xz_rectangle(size, size);
}

Primitive raytracer::primitives::yz_square(double size)
{
    return yz_rectangle(size, size);
}
