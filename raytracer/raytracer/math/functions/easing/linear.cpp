#include "math/functions/easing/linear.h"
#include <assert.h>
#include <math.h>

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
