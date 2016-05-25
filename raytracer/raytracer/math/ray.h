#pragma once

#include "math/vector3d.h"
#include "math/point3d.h"

namespace math
{
	struct ray final
	{
		point3d origin;
		vector3d direction;

		ray(const point3d& origin, const vector3d& direction)
			: origin(origin), direction(direction) { }

		ray(const ray&) = default;

		point3d at(double t) const { return origin + direction * t; }
	};
}