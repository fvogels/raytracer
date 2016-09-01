#include "math/functions/easing/elastic-easing-function.h"
#include "math/angle.h"
#include "math/interval.h"
#include "easylogging++.h"
#include <assert.h>
#include <cmath>

using namespace math;
using namespace math::functions;


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
