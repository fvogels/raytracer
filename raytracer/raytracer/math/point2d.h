#pragma once

#include "math/vector2d.h"

namespace math
{
	struct point2d final
	{
		double x, y;

		point2d()
			: x(0), y(0) { }

		point2d(double x, double y)
			: x(x), y(y) { }

		point2d(const point2d& v) = default;

		point2d& operator =(const point2d&) = default;
	};

	point2d operator +(const point2d&, const vector2d&);
	point2d operator +(const vector2d&, const point2d&);
	vector2d operator -(const point2d&, const point2d&);
	point2d operator -(const point2d&, const vector2d&);

	double distance(const point2d&, const point2d&);
}
