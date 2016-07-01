#include "primitives/primitives.h"
#include "primitives/primitive.h"
#include "primitives/plane.h"
#include "primitives/sphere.h"
#include "primitives/cylinder.h"
#include "primitives/union.h"
#include "primitives/intersection.h"
#include "primitives/transformer.h"
#include "primitives/decorator.h"
#include "primitives/cropper.h"
#include "math/transformation.h"

using namespace raytracer;
using namespace raytracer::primitives;


Primitive raytracer::primitives::transform(const math::Transformation& transformation, Primitive transformee)
{
    return Primitive(std::make_shared<Transformer>(transformation, transformee));
}

Primitive raytracer::primitives::translate(const math::Vector3D& v, Primitive transformee)
{
    return transform(math::translation(v), transformee);
}

Primitive raytracer::primitives::scale(double x, double y, double z, Primitive transformee)
{
    return transform(math::scale(x, y, z), transformee);
}

Primitive raytracer::primitives::rotate_around_x(math::Angle angle, Primitive transformee)
{
    return transform(math::rotate_x(angle), transformee);
}

Primitive raytracer::primitives::rotate_around_y(math::Angle angle, Primitive transformee)
{
    return transform(math::rotate_y(angle), transformee);
}

Primitive raytracer::primitives::rotate_around_z(math::Angle angle, Primitive transformee)
{
    return transform(math::rotate_z(angle), transformee);
}
