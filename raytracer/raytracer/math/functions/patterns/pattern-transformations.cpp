#include "math/functions/patterns/pattern-transformations.h"
#include "math/functions/patterns/lambda-pattern.h"
#include <cmath>


using namespace math::functions;
using namespace math::functions::patterns;



Pattern2D math::functions::patterns::transform(const math::Transformation2D& transformation, Pattern2D pattern)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        return pattern(transformation.inverse_transformation_matrix * point);
    };

    return make_pattern(function);
}

Pattern2D math::functions::patterns::translate(math::Vector2D displacement, Pattern2D pattern)
{
    return transform(math::transformations::translation(displacement), pattern);
}

Pattern2D math::functions::patterns::rotate(math::Angle angle, Pattern2D pattern)
{
    return transform(math::transformations::rotate(angle), pattern);
}

Pattern2D math::functions::patterns::scale(double sx, double sy, Pattern2D pattern)
{
    return transform(math::transformations::scale(sx, sy), pattern);
}
