#pragma once

#include "imaging/color.h"
#include "math/Point3D.h"

namespace Raytracer 
{
	class Material3D
	{
	public:
		virtual color at(const math::Point3D&) const = 0;
	};
}