#include "patterns/polar-pattern.h"
#include "math/coordinate-systems.h"


using namespace patterns;
using namespace math;


Pattern2D patterns::make_pattern(std::function<bool(double, math::Angle)> function)
{
    std::function<bool(const Point2D&)> f = [=](const Point2D& point)
    {
        const auto x = point.x();
        const auto y = point.y();
        const auto polar = convert_coordinates<Polar>(Cartesian2D{ x, y });

        return function(polar.radius, polar.theta);
    };

    return make_pattern(f);
}
