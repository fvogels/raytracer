#include "math/functions/patterns/lines-pattern.h"
#include "math/functions/patterns/lambda-pattern.h"
#include "math/functions/patterns/pattern-tessellation.h"
#include "math/functions/patterns/pattern-transformations.h"
#include <cmath>


using namespace math::functions;


Pattern2D math::functions::patterns::lines(double thickness, double separation, math::Angle angle)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return point.y() < thickness;
    };

    return rotate(angle, tessellate_y(make_pattern(function), thickness + separation));
}