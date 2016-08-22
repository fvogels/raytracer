#pragma once

#include "math/matrix.h"
#include "math/angle.h"


namespace math
{
    namespace transformation_matrices
    {
        Matrix4D coordinate_system(const Point3D&, const Vector3D&, const Vector3D&, const Vector3D&);
        Matrix3D translation(const Vector2D&);
        Matrix4D translation(const Vector3D&);
        Matrix3D scaling(double sx, double sy);
        Matrix4D scaling(double sx, double sy, double sz);
        Matrix3D rotation(Angle);
        Matrix4D rotation_around_x(Angle);
        Matrix4D rotation_around_y(Angle);
        Matrix4D rotation_around_z(Angle);
    }
}
