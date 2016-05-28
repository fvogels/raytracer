#pragma once

#include "math/vector3d.h"
#include "math/point3d.h"
#include "math/matrix4d.h"

namespace math
{
	struct ray final
	{
		point3d origin;
		vector3d direction;

		ray(const point3d& origin, const vector3d& direction)
			: origin(origin), direction(direction) { }

		ray(const point3d& origin, const point3d& through)
			: ray(origin, through - origin) { }

		ray(const ray&) = default;

		point3d at(double t) const { return origin + direction * t; }

		ray transform(const matrix4d&) const;
	};
}