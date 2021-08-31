#pragma once

#include "math/function.h"
#include "math/point.h"
#include "math/functions/checkered-pattern.h"


namespace math
{
    namespace functions
    {
        math::Function<bool(const Point2D&)> polka(double radius);
        math::Function<bool(const Point2D&)> polka(double radius1, double radius2);
    }
}
