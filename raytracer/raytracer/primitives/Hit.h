#pragma once

#include "math/vector3d.h"
#include "math/point3D.h"
#include "imaging/color.h"
#include <limits>

namespace Raytracer
{
	struct Hit
	{
		double t;
		math::Point3D position;
		math::vector3d normal;
		color c;

		Hit() : t( std::numeric_limits<double>::infinity()) { }
	};
}