#include "patterns/split-pattern.h"
#include "patterns/lambda-pattern.h"


using namespace math;
using namespace patterns;


Pattern2D patterns::xsplit(double boundary)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return point.x() < boundary;
    };

    return make_pattern(function);
}

Pattern2D patterns::ysplit(double boundary)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return point.y() < boundary;
    };

    return make_pattern(function);
}
