#pragma once

#include "math/vector3d.h"
#include "math/point3d.h"
#include "imaging/color.h"
#include "materials/material3d.h"
#include <limits>
#include <memory>

namespace raytracer
{
	struct Hit
	{
		double t;
		math::Point3D position;
		math::Vector3D normal;
		color c;
		std::shared_ptr<Material3D> material;

		Hit() : t( std::numeric_limits<double>::infinity()) { }
	};
}