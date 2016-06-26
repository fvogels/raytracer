#pragma once

#include "math/function.h"
#include "math/point2d.h"


namespace math
{
    namespace functions
    {
        math::Function<bool, const Point2D&> checkered();
        math::Function<bool, const Point2D&> horizontal_lines(double thickness = 0.1);
        math::Function<bool, const Point2D&> vertical_lines(double thickness = 0.1);
        math::Function<bool, const Point2D&> grid(double thickness = 0.1);
    }
}