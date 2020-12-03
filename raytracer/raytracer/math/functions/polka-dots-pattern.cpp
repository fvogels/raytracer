#include "math/functions/polka-dots-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::polka(double radius)
{
    auto radius_sqr = radius * radius;

    std::function<bool(const Point2D&)> function = [=](const Point2D& p)
    {
        auto x = p.x();
        auto y = p.y();

        auto cx = floor(x) + 0.5;
        auto cy = floor(y) + 0.5;
        Point2D fp(cx, cy);

        auto d_sqr = distance_sqr(p, fp);

        return d_sqr < radius_sqr;
    };

    return from_lambda<bool, const Point2D&>(function);
}
