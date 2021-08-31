#include "math/functions/patterns/lines-pattern.h"
#include "math/functions/patterns/lambda-pattern.h"
#include "math/functions/patterns/pattern-operations.h"
#include <cmath>


using namespace math::functions;


Pattern2D math::functions::patterns::lines(double thickness, double separation, math::Angle angle)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        const auto y = point.y();
        const auto total_size = thickness + separation;
        const auto canonical_y = fmod(fmod(y, total_size) + total_size, total_size);

        return canonical_y < thickness;
    };

    return rotate(angle, make_pattern(function));
}