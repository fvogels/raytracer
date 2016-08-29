#pragma once

#include "math/matrix.h"
#include "math/angle.h"

namespace math
{
    class Transformation2D
    {
    public:
        Transformation2D(const Matrix3D& transformation_matrix, const Matrix3D& inverse_transformation_matrix)
            : transformation_matrix(transformation_matrix), inverse_transformation_matrix(inverse_transformation_matrix) { }

        Matrix3D transformation_matrix;
        Matrix3D inverse_transformation_matrix;
    };

    namespace transformations
    {
        Transformation2D translation(const Vector2D&);
        Transformation2D scale(double, double);
        Transformation2D rotate(Angle);
    }
}
