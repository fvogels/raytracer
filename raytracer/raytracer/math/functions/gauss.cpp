#include "math/functions/gauss.h"
#include <cmath>

using namespace math;


Function<double(double)> math::functions::gauss(double center, double width)
{
    std::function<double(double)> lambda = [center, width](double t) {
        return exp(pow((t - center) / width, 2));
    };

    return from_lambda(lambda);
}