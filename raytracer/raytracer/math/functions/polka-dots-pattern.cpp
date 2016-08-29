#include "math/functions/polka-dots-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::polka(double radius1, double radius2)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& p)
    {
        auto x = p.x();
        auto y = p.y();

        auto fx = x - floor(x);
        auto fy = y - floor(y);

        Point2D fp(fx, fy);

#       define CHECK(X, Y, R)   distance(fp, Point2D(X, Y)) < R
        return CHECK(0.5, 0.5, radius1) || CHECK(0, 0, radius2) || CHECK(1, 0, radius2) || CHECK(0, 1, radius2) || CHECK(1, 1, radius2);
#       undef CHECK
    };

    return from_lambda<bool, const Point2D&>(function);
}

Function<bool(const Point2D&)> math::functions::polka(double radius)
{
    return polka(radius, radius);
}
