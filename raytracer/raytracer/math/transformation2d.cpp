#include "math/transformation2d.h"
#include "math/transformation-matrices.h"

using namespace math;


Transformation2D math::transformations::translation(const Vector2D& v)
{
    Matrix3D tm = transformation_matrices::translation(v);
    Matrix3D itm = transformation_matrices::translation(-v);

    return Transformation2D(tm, itm);
}

Transformation2D math::transformations::scale(double sx, double sy)
{
    Matrix3D tm = transformation_matrices::scaling(sx, sy);
    Matrix3D itm = transformation_matrices::scaling(1 / sx, 1 / sy);

    return Transformation2D(tm, itm);
}

Transformation2D math::transformations::rotate(Angle angle)
{
    Matrix3D tm = transformation_matrices::rotation(angle);
    Matrix3D itm = transformation_matrices::rotation(-angle);

    return Transformation2D(tm, itm);
}
