#pragma once

#include "vector3d.h"

namespace math
{
	struct point3d
	{
		double x, y, z;

		point3d()
			: x(0), y(0), z(0) { }

		point3d(double x, double y, double z)
			: x(x), y(y), z(z) { }

		point3d(const point3d& v) = default;

		point3d& operator =(const point3d&) = default;
	};

	point3d operator +(const point3d&, const vector3d&);
	point3d operator +(const vector3d&, const point3d&);
	vector3d operator -(const point3d&, const point3d&);
}
