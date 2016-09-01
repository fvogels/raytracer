#pragma once

#include "math/function.h"
#include "math/functions.h"
#include "math/interval.h"


namespace math
{
    namespace functions
    {
        typedef math::Function<double(double)> EasingFunction;

        namespace easing
        {
            math::functions::EasingFunction linear();
            math::functions::EasingFunction quadratic_in();
            math::functions::EasingFunction quadratic_out();
            math::functions::EasingFunction quadratic_inout();
            math::functions::EasingFunction cubic_in();
            math::functions::EasingFunction cubic_out();
            math::functions::EasingFunction cubic_inout();
            math::functions::EasingFunction quintic_in();
            math::functions::EasingFunction quintic_out();
            math::functions::EasingFunction quintic_inout();
            math::functions::EasingFunction bounce(unsigned bounce_count, double bounce_absorption);

            math::functions::EasingFunction stretch_horizontally(EasingFunction function, const math::Interval<double>& x_range);
            math::functions::EasingFunction stretch_vertically(EasingFunction function, const math::Interval<double>& y_range);
            math::functions::EasingFunction stretch(EasingFunction function, const math::Interval<double>& x_range, const math::Interval<double>& y_range);
        }
    }
}