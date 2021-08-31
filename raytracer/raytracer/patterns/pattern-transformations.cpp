#include "patterns/pattern-transformations.h"
#include "patterns/lambda-pattern.h"
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

Pattern3D math::functions::patterns::transform(const math::Transformation3D& transformation, Pattern3D pattern)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
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

Pattern3D math::functions::patterns::translate(math::Vector3D displacement, Pattern3D pattern)
{
    return transform(math::transformations::translation(displacement), pattern);
}

Pattern3D math::functions::patterns::rotate_x(math::Angle angle, Pattern3D pattern)
{
    return transform(math::transformations::rotate_x(angle), pattern);
}

Pattern3D math::functions::patterns::rotate_y(math::Angle angle, Pattern3D pattern)
{
    return transform(math::transformations::rotate_y(angle), pattern);
}

Pattern3D math::functions::patterns::rotate_z(math::Angle angle, Pattern3D pattern)
{
    return transform(math::transformations::rotate_z(angle), pattern);
}

Pattern3D math::functions::patterns::scale(double sx, double sy, double sz, Pattern3D pattern)
{
    return transform(math::transformations::scale(sx, sy, sz), pattern);
}
