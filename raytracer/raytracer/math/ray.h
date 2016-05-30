#pragma once

#include "math/vector3d.h"
#include "math/point3d.h"
#include "math/Matrix4D.h"

namespace math
{
	struct Ray final
	{
		point3d origin;
		vector3d direction;

		Ray(const point3d& origin, const vector3d& direction)
			: origin(origin), direction(direction) { }

		Ray(const point3d& origin, const point3d& through)
			: Ray(origin, through - origin) { }

		Ray(const Ray&) = default;

		point3d at(double t) const { return origin + direction * t; }

		Ray transform(const Matrix4D&) const;
	};
}