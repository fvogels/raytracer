#pragma once

#include "math/vector3d.h"
#include "math/point3d.h"
#include <limits>

namespace raytracer
{
	struct Hit
	{
		double t;
		math::point3d position;
		math::vector3d normal;

		Hit() : t( std::numeric_limits<double>::infinity()) { }
	};
}