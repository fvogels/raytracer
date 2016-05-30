#pragma once

#include "math/Matrix4D.h"

namespace math
{
	class transformation
	{
	public:
		transformation(const Matrix4D& transformation_matrix, const Matrix4D& inverse_transformation_matrix)
			: transformation_matrix(transformation_matrix), inverse_transformation_matrix(inverse_transformation_matrix)  { }
	
		Matrix4D transformation_matrix;
		Matrix4D inverse_transformation_matrix;
	};

	transformation translation(const vector3d&);
	transformation scale(double, double, double);
}