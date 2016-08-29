#pragma once

#include "math/function.h"
#include "math/point.h"
#include "math/functions/checkered.h"


namespace math
{
    namespace functions
    {
        math::Function<bool(const Point2D&)> horizontal_lines(double thickness = 0.1);
        math::Function<bool(const Point2D&)> vertical_lines(double thickness = 0.1);
        math::Function<bool(const Point2D&)> grid(double thickness = 0.1);
        math::Function<bool(const Point2D&)> polka(double radius = 0.25);
        math::Function<bool(const Point2D&)> polka2(unsigned density, unsigned seed = 46776);
    }
}