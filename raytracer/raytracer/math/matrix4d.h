#pragma once

#include "math/vector3d.h"
#include "math/point3d.h"

namespace math
{
	struct matrix4d
	{
		double
			x11, x12, x13, x14,
			x21, x22, x23, x24,
			x31, x32, x33, x34,
			x41, x42, x43, x44;
	};

	matrix4d operator *(const matrix4d&, const matrix4d&);
	vector3d operator *(const matrix4d&, const vector3d&);
	point3d operator *(const matrix4d&, const point3d&);

	matrix4d identity_matrix();
	matrix4d translation_matrix(const vector3d&);
	matrix4d scale_matrix(double sx, double sy, double sz);
}