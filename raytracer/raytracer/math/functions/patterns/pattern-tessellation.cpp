#include "math/functions/patterns/pattern-tessellation.h"
#include "math/functions/patterns/lambda-pattern.h"
#include <cmath>


using namespace math::functions;
using namespace math::functions::patterns;



Pattern2D math::functions::patterns::tessellate(Pattern2D pattern, double width, double height)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        const auto x = fmod(fmod(point.x(), width) + width, width);
        const auto y = fmod(fmod(point.y(), height) + height, height);

        return pattern(Point2D(x, y));
    };

    return make_pattern(function);
}

Pattern2D math::functions::patterns::tessellate_x(Pattern2D pattern, double width)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        const auto x = fmod(fmod(point.x(), width) + width, width);
        const auto y = point.y();

        return pattern(Point2D(x, y));
    };

    return make_pattern(function);
}

Pattern2D math::functions::patterns::tessellate_y(Pattern2D pattern, double height)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        const auto x = point.x();
        const auto y = fmod(fmod(point.y(), height) + height, height);

        return pattern(Point2D(x, y));
    };

    return make_pattern(function);
}
