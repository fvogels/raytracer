#pragma once

#include "math/Point2D.h"
#include "math/Point3D.h"

namespace math
{
	struct rectangle3d
	{
		Point3D origin;
		vector3d x_axis;
		vector3d y_axis;

		rectangle3d(const Point3D& origin, const vector3d& x_axis, const vector3d& y_axis)
			: origin(origin), x_axis(x_axis), y_axis(y_axis) { }

		Point3D project(const Point2D&) const;
	};
}