#pragma once

#include "primitives/primitive.h"
#include "math/function.h"
#include "math/interval.h"


namespace raytracer
{
    namespace primitives
    {
        Primitive crop(Primitive, math::Function<bool(const math::Point3D&)>, const math::Box&);
        Primitive crop(Primitive, math::Function<bool(const math::Point3D&)>);
        Primitive crop_along_x(Primitive, const math::Interval<double>&);
        Primitive crop_along_y(Primitive, const math::Interval<double>&);
        Primitive crop_along_z(Primitive, const math::Interval<double>&);
        Primitive crop_by_box(Primitive, const math::Box&);
        Primitive crop_spherical(Primitive, double radius);
    }
}