#pragma once

#include "imaging/color.h"
#include "math/point3d.h"

namespace raytracer 
{
	class Material3D
	{
	public:
		virtual color at(const math::point3d&) const = 0;
	};
}