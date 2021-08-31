#include "patterns/polka-dots-pattern.h"
#include "patterns/pattern-tessellation.h"
#include "patterns/lambda-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


math::functions::Pattern2D math::functions::patterns::polka(double radius, double separation)
{
    auto radius_sqr = radius * radius;
    auto center = separation / 2;

    std::function<bool(const Point2D&)> function = [=](const Point2D& p)
    {
        auto x = p.x();
        auto y = p.y();

        auto dx = x - center;
        auto dy = y - center;

        return dx * dx + dy * dy < radius_sqr;
    };

    return tessellate(make_pattern(function), separation, separation);
}
