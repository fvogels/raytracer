#include "math/functions/easing-functions.h"
#include <assert.h>

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
