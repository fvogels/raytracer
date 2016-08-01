#pragma once

#include "primitives/primitive.h"
#include "math/transformation.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        Primitive transform(const math::Transformation&, Primitive);
        Primitive translate(const math::Vector3D&, Primitive);
        Primitive scale(double, double, double, Primitive);
        Primitive rotate_around_x(math::Angle, Primitive);
        Primitive rotate_around_y(math::Angle, Primitive);
        Primitive rotate_around_z(math::Angle, Primitive);
        Primitive center(const math::Point3D&, Primitive);
    }
}