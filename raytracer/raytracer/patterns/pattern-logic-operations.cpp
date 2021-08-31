#include "patterns/pattern-logic-operations.h"
#include "patterns/lambda-pattern.h"
#include <cmath>

using namespace patterns;
using namespace math;


Pattern2D patterns::conjunction(Pattern2D pattern1, Pattern2D pattern2)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return pattern1(point) && pattern2(point);
    };

    return make_pattern(function);
}

Pattern2D patterns::disjunction(Pattern2D pattern1, Pattern2D pattern2)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return pattern1(point) || pattern2(point);
    };

    return make_pattern(function);
}

Pattern2D patterns::exclusive_disjunction(Pattern2D pattern1, Pattern2D pattern2)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return pattern1(point) != pattern2(point);
    };

    return make_pattern(function);
}

Pattern2D patterns::negation(Pattern2D pattern)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return !pattern(point);
    };

    return make_pattern(function);
}

Pattern3D patterns::conjunction(Pattern3D pattern1, Pattern3D pattern2)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
        return pattern1(point) && pattern2(point);
    };

    return make_pattern(function);
}

Pattern3D patterns::disjunction(Pattern3D pattern1, Pattern3D pattern2)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
        return pattern1(point) || pattern2(point);
    };

    return make_pattern(function);
}

Pattern3D patterns::exclusive_disjunction(Pattern3D pattern1, Pattern3D pattern2)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
        return pattern1(point) != pattern2(point);
    };

    return make_pattern(function);
}

Pattern3D patterns::negation(Pattern3D pattern)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
        return !pattern(point);
    };

    return make_pattern(function);
}
