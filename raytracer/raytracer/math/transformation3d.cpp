#include "math/transformation3d.h"
#include "math/transformation-matrices.h"

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

Transformation math::transformations::rotate_x(Angle angle)
{
    Matrix4D tm = transformation_matrices::rotation_around_x(angle);
    Matrix4D itm = transformation_matrices::rotation_around_x(-angle);

    return Transformation(tm, itm);
}

Transformation math::transformations::rotate_y(Angle angle)
{
    Matrix4D tm = transformation_matrices::rotation_around_y(angle);
    Matrix4D itm = transformation_matrices::rotation_around_y(-angle);

    return Transformation(tm, itm);
}

Transformation math::transformations::rotate_z(Angle angle)
{
    Matrix4D tm = transformation_matrices::rotation_around_z(angle);
    Matrix4D itm = transformation_matrices::rotation_around_z(-angle);

    return Transformation(tm, itm);
}

Transformation math::transformations::rotate_align_y(const Vector3D& y_axis)
{
    assert(y_axis.is_unit());

    Vector3D v = find_perpendicular_on(y_axis);

    assert(y_axis.is_perpendicular_on(v));

    Vector3D z_axis = v.cross(y_axis).normalized();
    Vector3D x_axis = z_axis.cross(y_axis).normalized();

    assert(x_axis.is_perpendicular_on(y_axis));
    assert(x_axis.is_perpendicular_on(z_axis));
    assert(y_axis.is_perpendicular_on(z_axis));
    assert(x_axis.is_unit());
    assert(y_axis.is_unit());
    assert(z_axis.is_unit());

    Matrix4D m = transformation_matrices::coordinate_system(Point3D(0, 0, 0), x_axis, y_axis, z_axis);
    Matrix4D inv_m = transpose(m);

    assert(m * inv_m == approx(identity<4>()));
    assert(inv_m * m == approx(identity<4>()));

    return Transformation(m, inv_m);
}