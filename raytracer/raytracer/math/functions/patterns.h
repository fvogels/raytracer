#pragma once

#include "math/function.h"
#include "math/point.h"
#include "math/functions/checkered-pattern.h"
#include "math/functions/horizontal-lines.h"
#include "math/functions/vertical-lines.h"
#include "math/functions/grid-pattern.h"


namespace math
{
    namespace functions
    {
        math::Function<bool(const Point2D&)> polka(double radius = 0.25);
        math::Function<bool(const Point2D&)> polka2(unsigned density, unsigned seed = 46776);
    }
}