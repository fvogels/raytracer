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

        if (t < -0.5)
        {
            return 2 * pow(t, 2);
        }
        else
        {
            return -2 * pow(t, 2) + 4 * t - 1;
        }
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::cubic_in()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return pow(t, 3);
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::cubic_out()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return pow(t, 3) - 3 * pow(t, 2) + 3 * t;
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::cubic_inout()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        if (t <= 0.5)
        {
            return 4 * pow(t, 3);
        }
        else
        {
            return 4 * pow(t, 3) - 12 * pow(t, 2) + 12 * t - 3;
        }
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::quintic_in()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return pow(t, 5);
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::quintic_out()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return t * (pow(t, 4) - 5 * pow(t, 3) + 10 * pow(t, 2) - 10 * t + 5);
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::quintic_inout()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        if (t <= 0.5)
        {
            return 16 * pow(t, 5);
        }
        else
        {
            return 16 * pow(t, 5) - 80 * pow(t, 4) + 160 * pow(t, 3) - 160 * pow(t, 2) + 80 * t - 15;
        }
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::_private_::bounce()
{
    std::function<double(double)> lambda = [](double t) {
        assert(Interval<double>(0, 1).contains(t));

        return 1 - abs(cos(5.5 * M_PI * t)) * exp(-3 * t);
    };

    return from_lambda(lambda);
}
