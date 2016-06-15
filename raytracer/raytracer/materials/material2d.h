#pragma once

#include "imaging/color.h"
#include "math/point2d.h"

namespace raytracer
{
	class Material2D
	{
	public:
		virtual color at(const math::Point2D&) const = 0;
	};
}