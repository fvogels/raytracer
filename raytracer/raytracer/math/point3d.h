#pragma once

#include "math/point.h"
#include "math/vector3d.h"

namespace math
{
    using Point3D = Point<3>;

    template<>
    struct approximately<Point3D>
    {
        Point3D value;
        double delta;

        explicit approximately(const Point3D& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const Point3D& other) const
        {
            return (value - other).norm() < delta;
        }
    };
}
