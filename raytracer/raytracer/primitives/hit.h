#pragma once

#include "math/vector3d.h"
#include "math/point2d.h"
#include "math/point3d.h"
#include "imaging/color.h"
#include "materials/material.h"
#include "primitives/hit-position.h"
#include <limits>
#include <memory>

namespace raytracer
{
	struct Hit
	{
		double t;
		HitPosition local_position;
		math::Point3D position;
		math::Vector3D normal;
		Material material;

		Hit() : t( std::numeric_limits<double>::infinity()) { }
	};
}