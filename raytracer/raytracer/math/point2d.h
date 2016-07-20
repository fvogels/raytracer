#pragma once

#include "math/point.h"
#include "math/vector2d.h"
#include "math/approx.h"


namespace math
{
    using Point2D = Point<2>;

    Point2D point(double radius, Angle theta)
    {
        return point(radius * cos(theta), radius * sin(theta));
    }
}
