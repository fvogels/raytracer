#pragma once

#include "math/functions/easing-function.h"
#include "math/interval.h"
#include "math/functions/easing/linear-easing-function.h"
#include "math/functions/easing/quadratic-easing-function.h"
#include "math/functions/easing/cubic-easing-function.h"
#include "math/functions/easing/quintic-easing-function.h"
#include "math/functions/easing/bounce-easing-function.h"


namespace math
{
    namespace functions
    {
        typedef math::Function<double(double)> EasingFunction;

        namespace easing
        {
            math::functions::EasingFunction elastic(unsigned count, double absorption);

            math::functions::EasingFunction stretch_in_time(EasingFunction function, const math::Interval<double>& x_range);
            math::functions::EasingFunction stretch_in_space(EasingFunction function, const math::Interval<double>& y_range);
            math::functions::EasingFunction stretch(EasingFunction function, const math::Interval<double>& x_range, const math::Interval<double>& y_range);
        }
    }
}