#include "math/functions/polka-dots-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::polka(double radius)
{
    std::function<bool(const Point2D&)> function = [radius](const Point2D& p)
    {
        auto x = p.x();
        auto y = p.y();

        auto fx = x - floor(x);
        auto fy = y - floor(y);

        Point2D fp(fx, fy);

        return distance(fp, Point2D(0.5, 0.5)) < radius;
    };

    return from_lambda<bool, const Point2D&>(function);
}
