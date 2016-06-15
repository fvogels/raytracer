#pragma once

#include "imaging/color.h"
#include "math/point3d.h"

namespace raytracer 
{
	class Material3D
	{
	public:
		virtual color at(const math::Point3D&) const = 0;
	};
}