#pragma once

#include "math/point2d.h"
#include "math/point3d.h"

namespace math
{
	struct rectangle3d
	{
		point3d origin;
		vector3d x_axis;
		vector3d y_axis;

		rectangle3d(const point3d& origin, const vector3d& x_axis, const vector3d& y_axis)
			: origin(origin), x_axis(x_axis), y_axis(y_axis) { }

		point3d project(const point2d&) const;
	};
}