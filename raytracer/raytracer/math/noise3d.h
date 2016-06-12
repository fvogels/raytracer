#pragma once

#include "math/point3d.h"


namespace math
{
	class Noise3D
	{
	public:
		virtual double operator [](const math::Point3D&) const = 0;
	};
}