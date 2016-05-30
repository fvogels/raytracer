#pragma once

#include "math/Matrix4D.h"

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

	Transformation translation(const vector3d&);
	Transformation scale(double, double, double);
}