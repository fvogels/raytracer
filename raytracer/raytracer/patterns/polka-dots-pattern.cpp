#include "patterns/polka-dots-pattern.h"
#include "patterns/pattern-tessellation.h"
#include "patterns/lambda-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;
using namespace patterns;


Pattern2D patterns::polka2d(double radius, double separation)
{
    auto radius_sqr = radius * radius;
    Point2D center(separation / 2, separation / 2);

    std::function<bool(const Point2D&)> function = [=](const Point2D& point)
    {
        return distance_sqr(center, point) < radius_sqr;
    };

    return tessellate(make_pattern(function), separation, separation);
}

Pattern3D patterns::polka3d(double radius, double separation)
{
    auto radius_sqr = radius * radius;
    Point3D center(separation / 2, separation / 2, separation / 2);

    std::function<bool(const Point3D&)> function = [=](const Point3D& point)
    {
        return distance_sqr(center, point) < radius_sqr;
    };

    return tessellate(make_pattern(function), separation, separation, separation);
}
