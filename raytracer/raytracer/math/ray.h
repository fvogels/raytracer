#pragma once

#include "math/vector3d.h"
#include "math/point3D.h"
#include "math/Matrix4D.h"

namespace math
{
	struct Ray final
	{
		Point3D origin;
		vector3d direction;

		Ray(const Point3D& origin, const vector3d& direction)
			: origin(origin), direction(direction) { }

		Ray(const Point3D& origin, const Point3D& through)
			: Ray(origin, through - origin) { }

		Ray(const Ray&) = default;

		Point3D at(double t) const { return origin + direction * t; }

		Ray transform(const Matrix4D&) const;
	};
}