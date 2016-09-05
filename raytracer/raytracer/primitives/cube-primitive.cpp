#define _USE_MATH_DEFINES
#include "primitives/cube-primitive.h"
#include "primitives/primitives.h"
#include <assert.h>
#include <cmath>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


Primitive raytracer::primitives::cube()
{
    auto bottom = square();
    auto top = translate(Vector3D(0, 1, 0), bottom);
    auto front = rotate_around_x(-90_degrees, bottom);
    auto back = translate(Vector3D(0, 0, 1), front);
    auto left = rotate_around_z(90_degrees, bottom);
    auto right = translate(Vector3D(1, 0, 0), left);

    std::vector<Primitive> sides = { bottom, top, front, back, left, right };

    return make_union(sides);
}