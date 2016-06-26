#pragma once

#include "math/vector2d.h"
#include "math/point2d.h"

namespace math
{
    struct Rectangle2D
    {
        Point2D origin;
        Vector2D x_axis;
        Vector2D y_axis;

        Rectangle2D(const Point2D& origin, const Vector2D& x_axis, const Vector2D& y_axis)
            : origin(origin), x_axis(x_axis), y_axis(y_axis) { }

        Point2D center() const;
    };

    bool operator ==(const Rectangle2D&, const Rectangle2D&);
    bool operator !=(const Rectangle2D&, const Rectangle2D&);
}