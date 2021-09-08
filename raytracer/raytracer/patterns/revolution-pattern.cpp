#include "patterns/revolution-pattern.h"
#include "patterns/lambda-pattern.h"
#include "math/point.h"
#include "math/coordinate-systems.h"

using namespace patterns;
using namespace math;


Pattern2D patterns::revolution(std::function<double(math::Angle)> function)
{
    std::function<bool(const Point2D&)> f = [=](const Point2D& point) -> bool {
        auto x = point.x();
        auto y = point.y();
        auto polar = convert_coordinates<Polar>(Cartesian2D{ x, y });

        auto max_d = function(polar.theta);
        auto d = polar.radius;

        return d < max_d;
    };

    return make_pattern(f);
}
