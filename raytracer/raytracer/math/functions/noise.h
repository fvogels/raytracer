#pragma once

#include "math/point2d.h"
#include "math/point3d.h"
#include "math/function.h"


namespace math
{
	namespace functions
	{
		typedef math::Function<double, const Point2D&> Noise2D;
		typedef math::Function<double, const Point3D&> Noise3D;

		Noise2D worley_noise2d();
	}
}