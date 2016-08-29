#pragma once

#include "math/function.h"
#include "math/point.h"
#include "math/functions/checkered-pattern.h"
#include "math/functions/horizontal-lines-pattern.h"
#include "math/functions/vertical-lines-pattern.h"
#include "math/functions/grid-pattern.h"


namespace math
{
    namespace functions
    {
        math::Function<bool(const Point2D&)> polka(double radius = 0.25);
    }
}
