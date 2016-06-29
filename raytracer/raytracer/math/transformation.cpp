#include "math/transformation.h"

using namespace math;

Transformation math::translation(const Vector3D& v)
{
    Matrix4D tm = translation_matrix(v);
    Matrix4D itm = translation_matrix(-v);

    return Transformation(tm, itm);
}

Transformation math::scale(double sx, double sy, double sz)
{
    Matrix4D tm = scale_matrix(sx, sy, sz);
    Matrix4D itm = scale_matrix(1 / sx, 1 / sy, 1 / sz);

    return Transformation(tm, itm);
}

Transformation math::rotate_x(const Angle& angle)
{
    Matrix4D tm = rotate_x_matrix(angle);
    Matrix4D itm = rotate_x_matrix(-angle);

    return Transformation(tm, itm);
}

Transformation math::rotate_y(const Angle& angle)
{
    Matrix4D tm = rotate_y_matrix(angle);
    Matrix4D itm = rotate_y_matrix(-angle);

    return Transformation(tm, itm);
}

Transformation math::rotate_z(const Angle& angle)
{
    Matrix4D tm = rotate_z_matrix(angle);
    Matrix4D itm = rotate_z_matrix(-angle);

    return Transformation(tm, itm);
}
