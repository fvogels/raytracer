#pragma once

#include "math/vector.h"
#include "math/point.h"
#include "math/angle.h"
#include "math/approx.h"


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
    Matrix4D transpose(const Matrix4D&);

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

    template<>
    struct approximately<Matrix4D>
    {
        Matrix4D value;
        double delta;

        explicit approximately(const Matrix4D& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const Matrix4D& other) const
        {
            return
                value.x11 == approx(other.x11) &&
                value.x12 == approx(other.x12) &&
                value.x13 == approx(other.x13) &&
                value.x14 == approx(other.x14) &&
                value.x21 == approx(other.x21) &&
                value.x22 == approx(other.x22) &&
                value.x23 == approx(other.x23) &&
                value.x24 == approx(other.x24) &&
                value.x31 == approx(other.x31) &&
                value.x32 == approx(other.x32) &&
                value.x33 == approx(other.x33) &&
                value.x34 == approx(other.x34) &&
                value.x41 == approx(other.x41) &&
                value.x42 == approx(other.x42) &&
                value.x43 == approx(other.x43) &&
                value.x44 == approx(other.x44);
        }
    };
}