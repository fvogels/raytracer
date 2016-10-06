#include "math/functions/checkered-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::checkered2d()
{
    std::function<bool(const Point2D&)> function = [](const Point2D& p)
    {
        double x = p.x() - floor(p.x());
        double y = p.y() - floor(p.y());

        return (x < 0.5) != (y < 0.5);
    };

    return from_lambda<bool, const Point2D&>(function);
}
