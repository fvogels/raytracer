#include "patterns/pattern-logic-operations.h"
#include "patterns/lambda-pattern.h"
#include <cmath>


using namespace math::functions;
using namespace math::functions::patterns;


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

Pattern2D math::functions::patterns::exclusive_disjunction(Pattern2D pattern1, Pattern2D pattern2)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return pattern1(point) != pattern2(point);
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

Pattern3D math::functions::patterns::conjunction(Pattern3D pattern1, Pattern3D pattern2)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
        return pattern1(point) && pattern2(point);
    };

    return make_pattern(function);
}

Pattern3D math::functions::patterns::disjunction(Pattern3D pattern1, Pattern3D pattern2)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
        return pattern1(point) || pattern2(point);
    };

    return make_pattern(function);
}

Pattern3D math::functions::patterns::exclusive_disjunction(Pattern3D pattern1, Pattern3D pattern2)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
        return pattern1(point) != pattern2(point);
    };

    return make_pattern(function);
}

Pattern3D math::functions::patterns::negation(Pattern3D pattern)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
        return !pattern(point);
    };

    return make_pattern(function);
}
