#pragma once

#include "math/function.h"


namespace math
{
    namespace functions
    {
        math::Function<double, double> gauss(double center, double width);
    }
}