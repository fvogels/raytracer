#define _USE_MATH_DEFINES
#include "math/functions/easing-functions.h"
#include <assert.h>
#include <math.h>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::_private_::linear()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return t;
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::quadratic_in()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return t * t;
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::quadratic_out()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return 2 * t - t * t;
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::quadratic_inout()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return (3 - 2 * t) * t * t;
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::bounce()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return 1-abs(cos(5.5 * M_PI * t)) * exp(-3 * t);
    };

    return from_lambda(lambda);
}
