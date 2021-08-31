#pragma once

#include "math/functions/pattern.h"
#include "math/point.h"


namespace math
{
    namespace functions
    {
        namespace patterns
        {
            Pattern2D polka(double radius, double separation);
            // math::Function<bool(const Point2D&)> polka(double radius1, double radius2);
        }
    }
}
