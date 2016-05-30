#pragma once

#include "math/point2d.h"
#include "math/point3d.h"

namespace math
{
	struct Rectangle3D
	{
		Point3D origin;
		vector3d x_axis;
		vector3d y_axis;

		Rectangle3D(const Point3D& origin, const vector3d& x_axis, const vector3d& y_axis)
			: origin(origin), x_axis(x_axis), y_axis(y_axis) { }

		Point3D project(const Point2D&) const;
	};
}