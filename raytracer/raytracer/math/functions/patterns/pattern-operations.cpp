#include "math/functions/patterns/pattern-operations.h"
#include "math/functions/patterns/lambda-pattern.h"
#include <cmath>


using namespace math::functions;
using namespace math::functions::patterns;



Pattern2D math::functions::patterns::transform(const math::Transformation2D& transformation, Pattern2D pattern)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return pattern(transformation.inverse_transformation_matrix * point);
    };

    return make_pattern(function);
}

Pattern2D math::functions::patterns::translate(math::Vector2D displacement, Pattern2D pattern)
{
    return transform(math::transformations::translation(displacement), pattern);
}

Pattern2D math::functions::patterns::rotate(math::Angle angle, Pattern2D pattern)
{
    return transform(math::transformations::rotate(angle), pattern);
}

Pattern2D math::functions::patterns::scale(double sx, double sy, Pattern2D pattern)
{
    return transform(math::transformations::scale(sx, sy), pattern);
}

Pattern2D math::functions::patterns::conjunction(Pattern2D pattern1, Pattern2D pattern2)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return pattern1(point) && pattern2(point);
    };

    return make_pattern(function);
}

Pattern2D math::functions::patterns::disjunction(Pattern2D pattern1, Pattern2D pattern2)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return pattern1(point) || pattern2(point);
    };

    return make_pattern(function);
}

Pattern2D math::functions::patterns::negation(Pattern2D pattern)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return !pattern(point);
    };

    return make_pattern(function);
}

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
