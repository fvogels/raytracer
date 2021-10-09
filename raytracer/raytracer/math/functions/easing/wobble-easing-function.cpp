#include "math/functions/easing/wobble-easing-function.h"
#include "math/interval.h"
#include "math/angle.h"
#include <assert.h>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::wobble(unsigned nwobbles, double wobble_amplitude)
{
    std::function<double(double)> lambda = [=](double t) {
        assert(interval(0.0, 1.0).contains(t));

        return t + wobble_amplitude * sin(360_degrees * nwobbles);
    };

    return from_lambda(lambda);
}
