#define _USE_MATH_DEFINES
#include "math/functions.h"
#include "math/functions/easing-functions.h"
#include "math/angle.h"
#include "easylogging++.h"
#include <assert.h>
#include <cmath>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::stretch_in_time(EasingFunction function, const Interval<double>& x_range)
{
    return (identity<double>() - x_range.lower) >> (identity<double>() / x_range.size()) >> function;
}

EasingFunction math::functions::easing::stretch_in_space(EasingFunction function, const Interval<double>& y_range)
{
    return function * y_range.size() + y_range.lower;
}

EasingFunction math::functions::easing::stretch(EasingFunction function, const Interval<double>& x_range, const Interval<double>& y_range)
{
    return stretch_in_time(stretch_in_space(function, y_range), x_range);
}
