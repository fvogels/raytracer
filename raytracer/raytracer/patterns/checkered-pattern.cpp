#include "patterns/checkered-pattern.h"
#include "patterns/pattern-tessellation.h"
#include "patterns/lambda-pattern.h"
#include <cmath>

using namespace math;


math::functions::Pattern2D math::functions::patterns::checkered(double xthickness, double ythickness)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point)
    {
        return (point.x() < xthickness) != (point.y() < ythickness);
    };

    return tessellate(make_pattern(function), 2 * xthickness, 2 * ythickness);
}
//
//Function<bool(const Point3D&)> math::functions::checkered3d()
//{
//    std::function<bool(const Point3D&)> function = [](const Point3D& p)
//    {
//        double x = floor(p.x());
//        double y = floor(p.y());
//        double z = floor(p.z());
//
//        return std::abs(fmod(x + y + z, 2)) < 0.05;
//    };
//
//    return from_lambda<bool, const Point3D&>(function);
//}
