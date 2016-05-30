#pragma once

#include "math/matrix4d.h"

namespace math
{
	class Transformation
	{
	public:
		Transformation(const Matrix4D& Transformation_matrix, const Matrix4D& inverse_Transformation_matrix)
			: Transformation_matrix(Transformation_matrix), inverse_Transformation_matrix(inverse_Transformation_matrix)  { }
	
		Matrix4D Transformation_matrix;
		Matrix4D inverse_Transformation_matrix;
	};

	Transformation translation(const Vector3D&);
	Transformation scale(double, double, double);
}