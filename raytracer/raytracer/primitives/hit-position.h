#pragma once

#include "math/point2d.h"
#include "math/point3d.h"


namespace raytracer
{
	struct HitPosition
	{
		math::Point2D uv;
		math::Point3D xyz;
	};
}