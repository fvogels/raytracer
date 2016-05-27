#pragma once

#include "math/vector2d.h"
#include "math/point2d.h"

namespace math
{
	struct rectangle2d
	{
		point2d origin;
		vector2d x_axis;
		vector2d y_axis;

		rectangle2d(const point2d& origin, const vector2d& x_axis, const vector2d& y_axis)
			: origin(origin), x_axis(x_axis), y_axis(y_axis) { }
	};
}