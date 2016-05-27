#pragma once

#include "math/vector3d.h"

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

	matrix4d translation_matrix(const vector3d&);
}