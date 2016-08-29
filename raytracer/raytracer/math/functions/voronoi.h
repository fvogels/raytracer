#pragma once

#include "math/function.h"
#include "math/point.h"


namespace math
{
    namespace functions
    {
        math::Function<math::Point2D(const math::Point2D&)> voronoi2d(unsigned seed);
    }
}