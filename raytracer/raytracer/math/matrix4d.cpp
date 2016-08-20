#include "math/matrix4d.h"
#include <assert.h>

using namespace math;

Matrix4D math::operator *(const Matrix4D& a, const Matrix4D& b)
{
    Matrix4D result = transformation_matrices::zero();

    for (unsigned row = 0; row != 4; ++row)
    {
        for (unsigned col = 0; col != 4; ++col)
        {
            double& target = result.at(row, col);
            target = 0;

            for (unsigned i = 0; i != 4; ++i)
            {
                target += a.at(row, i) * b.at(i, col);
            }
        }
    }

    return result;
}

Vector3D math::operator *(const Matrix4D& a, const Vector3D& v)
{
#define AUX(row) a.at(row, 0) * v.x() + a.at(row, 1) * v.y() + a.at(row, 2) * v.z()

    double x = AUX(0);
    double y = AUX(1);
    double z = AUX(2);

    return Vector3D(x, y, z);

#undef AUX
}

Point3D math::operator *(const Matrix4D& a, const Point3D& p)
{
#define AUX(row) a.at(row, 0) * p.x() + a.at(row, 1) * p.y() + a.at(row, 2) * p.z() + a.at(row, 3)

    double x = AUX(0);
    double y = AUX(1);
    double z = AUX(2);

    return Point3D(x, y, z);

#undef AUX
}

Matrix4D math::transformation_matrices::zero()
{
    std::array<double, 16> xs = {
        0, 0 , 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    return Matrix4D(xs);
}

Matrix4D math::transformation_matrices::identity()
{
    std::array<double, 16> xs = {
        1, 0 , 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    return Matrix4D(xs);
}

Matrix4D math::transformation_matrices::translation(const Vector3D& v)
{
    std::array<double, 16> xs = {
        1, 0 , 0, v.x(),
        0, 1, 0, v.y(),
        0, 0, 1, v.z(),
        0, 0, 0, 1
    };

    return Matrix4D(xs);
}

Matrix4D math::transformation_matrices::scaling(double sx, double sy, double sz)
{
    std::array<double, 16> xs = {
        sx, 0 , 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
    };

    return Matrix4D(xs);
}

Matrix4D math::transformation_matrices::rotation_around_x(const Angle& angle)
{
    double s = sin(angle);
    double c = cos(angle);

    std::array<double, 16> xs = {
        1, 0 , 0, 0,
        0, c, -s, 0,
        0, s, c, 0,
        0, 0, 0, 1
    };

    return Matrix4D(xs);
}

Matrix4D math::transformation_matrices::rotation_around_y(const Angle& angle)
{
    double s = sin(angle);
    double c = cos(angle);

    std::array<double, 16> xs = {
        c, 0 , s, 0,
        0, 1, 0, 0,
        -s, 0, c, 0,
        0, 0, 0, 1
    };

    return Matrix4D(xs);
}

Matrix4D math::transformation_matrices::rotation_around_z(const Angle& angle)
{
    double s = sin(angle);
    double c = cos(angle);

    std::array<double, 16> xs = {
        c, -s , 0, 0,
        s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    return Matrix4D(xs);
}

Matrix4D math::transformation_matrices::coordinate_system(const Point3D& origin, const Vector3D& x_axis, const Vector3D& y_axis, const Vector3D& z_axis)
{
    std::array<double, 16> xs = {
        x_axis.x(), y_axis.x(), z_axis.x(), origin.x(),
        x_axis.y(), y_axis.y(), z_axis.y(), origin.y(),
        x_axis.z(), y_axis.z(), z_axis.z(), origin.z(),
        0, 0, 0, 1
    };

    return Matrix4D(xs);
}

Matrix4D math::transpose(const Matrix4D& m)
{
    Matrix4D result = transformation_matrices::zero();

    for (unsigned row = 0; row != 4; ++row)
    {
        for (unsigned col = 0; col != 4; ++col)
        {
            result.at(row, col) = m.at(col, row);
        }
    }

    return result;
}

std::ostream& math::operator <<(std::ostream& out, const Matrix4D& m)
{
    return out << "Matrix4D";
}