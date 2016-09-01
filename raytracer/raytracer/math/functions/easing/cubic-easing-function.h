#pragma once

#include "math/functions/easing-function.h"
#include "math/interval.h"
#include "math/functions/easing/linear-easing-function.h"
#include "math/functions/easing/quadratic-easing-function.h"


namespace math
{
    namespace functions
    {
        namespace easing
        {
            math::functions::EasingFunction cubic_in();
            math::functions::EasingFunction cubic_out();
            math::functions::EasingFunction cubic_inout();
        }
    }
}