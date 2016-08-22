#pragma once

#include "math/matrix.h"
#include "math/angle.h"

namespace math
{
    class Transformation
    {
    public:
        Transformation(const Matrix4D& transformation_matrix, const Matrix4D& inverse_transformation_matrix)
            : transformation_matrix(transformation_matrix), inverse_transformation_matrix(inverse_transformation_matrix)  { }
    
        Matrix4D transformation_matrix;
        Matrix4D inverse_transformation_matrix;
    };

    namespace transformations
    {
        Transformation translation(const Vector3D&);
        Transformation scale(double, double, double);
        Transformation rotate_x(Angle);
        Transformation rotate_y(Angle);
        Transformation rotate_z(Angle);
        Transformation rotate_align_y(const Vector3D&);
    }
}