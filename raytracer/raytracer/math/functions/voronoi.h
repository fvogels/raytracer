#pragma once

#include "math/function.h"
#include "math/point.h"


namespace math
{
    namespace functions
    {
        math::Function<math::Point2D(const math::Point2D&)> voronoi2d(unsigned density, unsigned seed = 87);
        math::Function<math::Point3D(const math::Point3D&)> voronoi3d(unsigned density, unsigned seed = 87);
    }
}