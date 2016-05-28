#pragma once

#include "math/vector3d.h"
#include "math/point3d.h"

namespace raytracer
{
	struct Hit
	{
		double t;
		math::point3d position;
		math::vector3d normal;
	};
}