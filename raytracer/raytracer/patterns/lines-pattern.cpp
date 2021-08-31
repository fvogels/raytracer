#include "patterns/lines-pattern.h"
#include "patterns/lambda-pattern.h"
#include "patterns/pattern-tessellation.h"
#include "patterns/pattern-transformations.h"
#include <cmath>


using namespace math::functions;


Pattern2D math::functions::patterns::lines(double thickness, double separation)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return point.y() < thickness;
    };

    return tessellate_y(make_pattern(function), thickness + separation);
}