#pragma once

#include "math/point.h"
#include "math/vector3d.h"

namespace math
{
    using Point3D = Point<3>;

    Point3D point(double r, math::Angle azimuth, math::Angle altitude)
    {
        return point(r * cos(azimuth) * cos(altitude), r * sin(altitude), r * sin(azimuth) * cos(altitude));
    }

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
