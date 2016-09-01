#include "math/functions/easing/cubic-easing-function.h"
#include <cmath>
#include <assert.h>

using namespace math;
using namespace math::functions;


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
