#pragma once

#include "math/matrix4d.h"

namespace math
{
	class transformation
	{
	public:
		transformation(const matrix4d& transformation_matrix, const matrix4d& inverse_transformation_matrix)
			: transformation_matrix(transformation_matrix), inverse_transformation_matrix(inverse_transformation_matrix)  { }

	private:
		matrix4d transformation_matrix;
		matrix4d inverse_transformation_matrix;
	};

	transformation translation(const vector3d&);
}