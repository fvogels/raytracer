#include "math/transformation.h"

using namespace math;

Transformation math::transformations::translation(const Vector3D& v)
{
    Matrix4D tm = transformation_matrices::translation(v);
    Matrix4D itm = transformation_matrices::translation(-v);

    return Transformation(tm, itm);
}

Transformation math::transformations::scale(double sx, double sy, double sz)
{
    Matrix4D tm = transformation_matrices::scaling(sx, sy, sz);
    Matrix4D itm = transformation_matrices::scaling(1 / sx, 1 / sy, 1 / sz);

    return Transformation(tm, itm);
}

Transformation math::transformations::rotate_x(const Angle& angle)
{
    Matrix4D tm = transformation_matrices::rotation_around_x(angle);
    Matrix4D itm = transformation_matrices::rotation_around_x(-angle);

    return Transformation(tm, itm);
}

Transformation math::transformations::rotate_y(const Angle& angle)
{
    Matrix4D tm = transformation_matrices::rotation_around_y(angle);
    Matrix4D itm = transformation_matrices::rotation_around_y(-angle);

    return Transformation(tm, itm);
}

Transformation math::transformations::rotate_z(const Angle& angle)
{
    Matrix4D tm = transformation_matrices::rotation_around_z(angle);
    Matrix4D itm = transformation_matrices::rotation_around_z(-angle);

    return Transformation(tm, itm);
}
