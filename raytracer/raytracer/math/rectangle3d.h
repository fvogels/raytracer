#pragma once

#include "math/point.h"
#include "math/point.h"

namespace math
{
    struct Rectangle3D
    {
        Point3D origin;
        Vector3D x_axis;
        Vector3D y_axis;

        Rectangle3D(const Point3D& origin, const Vector3D& x_axis, const Vector3D& y_axis)
            : origin(origin), x_axis(x_axis), y_axis(y_axis) { }

        Point3D project(const Point2D&) const;
    };
}