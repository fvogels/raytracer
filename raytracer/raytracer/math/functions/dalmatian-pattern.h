#pragma once

#include "math/function.h"
#include "math/point.h"


namespace math
{
    namespace functions
    {
        math::Function<bool(const Point2D&)> dalmatian2d(unsigned density, unsigned seed);
        math::Function<bool(const Point3D&)> dalmatian3d(unsigned density, unsigned seed);
    }
}
