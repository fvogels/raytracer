#pragma once

#include "math/function.h"
#include "math/point.h"


namespace math
{
    namespace functions
    {
        math::Function<bool(const Point2D&)> chaotic_polka(unsigned density, unsigned seed);
    }
}
