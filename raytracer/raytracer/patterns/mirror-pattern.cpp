#include "patterns/mirror-pattern.h"
#include "patterns/lambda-pattern.h"

using namespace patterns;
using namespace math;


Pattern2D patterns::mirror(Pattern2D pattern)
{
    return mirror_y(mirror_x(pattern));
}

Pattern2D patterns::mirror_x(Pattern2D pattern)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        Point2D p(fabs(point.x()), point.y());

        return pattern(p);
    };

    return make_pattern(function);
}

Pattern2D patterns::mirror_y(Pattern2D pattern)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        Point2D p(point.x(), fabs(point.y()));

        return pattern(p);
    };

    return make_pattern(function);
}