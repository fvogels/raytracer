#pragma once

#include "math/matrix.h"
#include "math/angle.h"

namespace math
{
    class Transformation3D
    {
    public:
        Transformation3D(const Matrix4x4& transformation_matrix, const Matrix4x4& inverse_transformation_matrix)
            : transformation_matrix(transformation_matrix), inverse_transformation_matrix(inverse_transformation_matrix)  { }
    
        Matrix4x4 transformation_matrix;
        Matrix4x4 inverse_transformation_matrix;
    };

    namespace transformations
    {
        Transformation3D translation(const Vector3D&);
        Transformation3D scale(double, double, double);
        Transformation3D rotate_x(Angle);
        Transformation3D rotate_y(Angle);
        Transformation3D rotate_z(Angle);
        Transformation3D rotate_align_y(const Vector3D&);
    }
}
