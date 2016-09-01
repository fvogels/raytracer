#pragma once

#include "math/functions/easing-function.h"


namespace math
{
    namespace functions
    {
        typedef math::Function<double(double)> EasingFunction;

        namespace easing
        {
            math::functions::EasingFunction linear();
        }
    }
}