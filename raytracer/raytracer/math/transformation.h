#pragma once

#include "math/matrix4d.h"
#include "math/angle.h"

namespace math
{
    class Transformation
    {
    public:
        Transformation(const Matrix4D& Transformation_matrix, const Matrix4D& inverse_Transformation_matrix)
            : transformation_matrix(Transformation_matrix), inverse_Transformation_matrix(inverse_Transformation_matrix)  { }
    
        Matrix4D transformation_matrix;
        Matrix4D inverse_Transformation_matrix;
    };

    Transformation translation(const Vector3D&);
    Transformation scale(double, double, double);
    Transformation rotate_x(const Angle&);
    Transformation rotate_y(const Angle&);
    Transformation rotate_z(const Angle&);
}