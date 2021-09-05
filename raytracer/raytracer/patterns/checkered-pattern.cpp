#include "patterns/checkered-pattern.h"
#include "patterns/pattern-tessellation.h"
#include "patterns/lambda-pattern.h"
#include <cmath>

using namespace math;


patterns::Pattern2D patterns::checkered(double xthickness, double ythickness)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point)
    {
        return (point.x() < xthickness) != (point.y() < ythickness);
    };

    return tessellate(make_pattern(function), 2 * xthickness, 2 * ythickness);
}

patterns::Pattern3D patterns::checkered(double xthickness, double ythickness, double zthickness)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point)
    {
        return (point.x() < xthickness) != (point.y() < ythickness) != (point.z() < zthickness);
    };

    return tessellate(make_pattern(function), 2 * xthickness, 2 * ythickness, 2 * zthickness);
}

