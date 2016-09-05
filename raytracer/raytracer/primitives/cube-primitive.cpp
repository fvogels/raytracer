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
    auto bottom = translate(Vector3D(0, -1, 0), xz_square());
    auto top = translate(Vector3D(0, 1, 0), xz_square());
    auto front = translate(Vector3D(0, 0, 1), xy_square());
    auto back = translate(Vector3D(0, 0, -1), xy_square());
    auto left = translate(Vector3D(-1, 0, 0), yz_square());
    auto right = translate(Vector3D(1, 0, 0), yz_square());

    std::vector<Primitive> sides = { bottom, top, front, back, left, right };

    return make_union(sides);
}