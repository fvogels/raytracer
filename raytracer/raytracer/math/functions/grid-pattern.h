#pragma once

#include "math/function.h"
#include "math/point.h"


namespace math
{
    namespace functions
    {
        math::Function<bool(const Point2D&)> grid2d(double thickness = 0.1);
        math::Function<bool(const Point3D&)> grid3d(double thickness = 0.1);
    }
}