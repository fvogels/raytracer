#include "primitives/box-primitive.h"
#include "primitives/rectangle-primitive.h"
#include "primitives/transformer-primitive.h"
#include "primitives/union-primitive.h"
#include "primitives/unify.h"
#include <assert.h>
#include <cmath>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


Primitive raytracer::primitives::box(double x_size, double y_size, double z_size)
{
    auto bottom = translate(Vector3D(0, -y_size / 2, 0), xz_rectangle(x_size, z_size));
    auto top = translate(Vector3D(0, y_size / 2, 0), xz_rectangle(x_size, z_size));
    auto front = translate(Vector3D(0, 0, -z_size / 2), xy_rectangle(x_size, y_size));
    auto back = translate(Vector3D(0, 0, z_size / 2), xy_rectangle(x_size, y_size));
    auto left = translate(Vector3D(x_size / 2, 0, 0), yz_rectangle(y_size, z_size));
    auto right = translate(Vector3D(-x_size / 2, 0, 0), yz_rectangle(y_size, z_size));

    std::vector<Primitive> sides = { bottom, top, front, back, left, right };

    return unify(make_union(sides));
}
