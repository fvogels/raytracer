#pragma once

#include "math/vector3d.h"
#include "math/point3d.h"
#include "math/angle.h"

namespace math
{
    struct Matrix4D
    {
        double
            x11, x12, x13, x14,
            x21, x22, x23, x24,
            x31, x32, x33, x34,
            x41, x42, x43, x44;
    };

    Matrix4D operator *(const Matrix4D&, const Matrix4D&);
    Vector3D operator *(const Matrix4D&, const Vector3D&);
    Point3D operator *(const Matrix4D&, const Point3D&);

    namespace transformation_matrices
    {
        Matrix4D identity();
        Matrix4D coordinate_system(const Point3D&, const Vector3D&, const Vector3D&, const Vector3D&);
        Matrix4D translation(const Vector3D&);
        Matrix4D scaling(double sx, double sy, double sz);
        Matrix4D rotation_around_x(const Angle&);
        Matrix4D rotation_around_y(const Angle&);
        Matrix4D rotation_around_z(const Angle&);
    }
}