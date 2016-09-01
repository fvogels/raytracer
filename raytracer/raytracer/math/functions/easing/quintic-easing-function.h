#pragma once

#include "math/functions/easing-function.h"
#include "math/interval.h"

namespace math
{
    namespace functions
    {
        namespace easing
        {
            math::functions::EasingFunction quintic_in();
            math::functions::EasingFunction quintic_out();
            math::functions::EasingFunction quintic_inout();
        }
    }
}