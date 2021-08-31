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

Pattern3D patterns::polka3d(double radius, double separation)
{
    auto radius_sqr = radius * radius;
    auto center = separation / 2;

    std::function<bool(const Point3D&)> function = [=](const Point3D& p)
    {
        auto x = p.x();
        auto y = p.y();
        auto z = p.z();

        auto dx = x - center;
        auto dy = y - center;
        auto dz = z - center;

        return dx * dx + dy * dy + dz * dz < radius_sqr;
    };

    return tessellate(make_pattern(function), separation, separation, separation);
}
