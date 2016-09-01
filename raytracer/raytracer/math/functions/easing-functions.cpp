#define _USE_MATH_DEFINES
#include "math/functions/easing-functions.h"
#include "easylogging++.h"
#include <assert.h>
#include <math.h>
#include <cmath>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::linear()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

        return t;
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::quadratic_in()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

        return t * t;
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::quadratic_out()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

        return 2 * t - t * t;
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::quadratic_inout()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

        if (t < 0.5)
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

EasingFunction math::functions::easing::cubic_in()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

        return pow(t, 3);
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::cubic_out()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

        return pow(t, 3) - 3 * pow(t, 2) + 3 * t;
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::cubic_inout()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

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

EasingFunction math::functions::easing::quintic_in()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

        return pow(t, 5);
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::quintic_out()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

        return t * (pow(t, 4) - 5 * pow(t, 3) + 10 * pow(t, 2) - 10 * t + 5);
    };

    return from_lambda(lambda);
}

EasingFunction math::functions::easing::quintic_inout()
{
    std::function<double(double)> lambda = [](double t) {
        assert(interval(0.0, 1.0).contains(t));

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

EasingFunction math::functions::easing::bounce(unsigned count, double absorption)
{
    if (count == 0)
    {
        LOG(ERROR) << "Ccount must be at least 1";
        abort();
    }
    else
    {
        std::function<double(double)> lambda = [count, absorption](double t) {
            assert(interval(0.0, 1.0).contains(t));

            double result = 1 - std::abs(cos((count - 0.5) * 180_degrees * t)) * exp(-absorption * t);

            assert(interval(0.0, 1.0).contains(result));
            
            return result;
        };

        return from_lambda(lambda);
    }
}

EasingFunction math::functions::easing::elastic(unsigned count, double absorption)
{
    if (count == 0)
    {
        LOG(ERROR) << "Count must be at least 1";
        abort();
    }
    else
    {
        std::function<double(double)> lambda = [count, absorption](double t) {
            assert(interval(0.0, 1.0).contains(t));

            double result = 1 - cos((count - 0.5) * 180_degrees * t) * exp(-absorption * t);

            assert(interval(0.0, 1.0).contains(result));

            return result;
        };

        return from_lambda(lambda);
    }
}

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
