#pragma once

#include "math/functions/easing-function.h"
#include "math/interval.h"
#include "math/functions/easing/linear-easing-function.h"
#include "math/functions/easing/quadratic-easing-function.h"
#include "math/functions/easing/cubic-easing-function.h"

namespace math
{
    namespace functions
    {
        typedef math::Function<double(double)> EasingFunction;

        namespace easing
        {
            math::functions::EasingFunction quintic_in();
            math::functions::EasingFunction quintic_out();
            math::functions::EasingFunction quintic_inout();
            math::functions::EasingFunction bounce(unsigned count, double absorption);
            math::functions::EasingFunction elastic(unsigned count, double absorption);

            math::functions::EasingFunction stretch_in_time(EasingFunction function, const math::Interval<double>& x_range);
            math::functions::EasingFunction stretch_in_space(EasingFunction function, const math::Interval<double>& y_range);
            math::functions::EasingFunction stretch(EasingFunction function, const math::Interval<double>& x_range, const math::Interval<double>& y_range);
        }
    }
}