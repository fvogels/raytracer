#pragma once

#include "math/point2d.h"


namespace math
{
	class Noise2D
	{
	public:
		virtual double operator [](const math::Point2D&) const = 0;
	};
}