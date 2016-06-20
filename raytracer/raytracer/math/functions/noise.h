#pragma once

#include "math/point2d.h"
#include "math/point3d.h"
#include "math/function.h"


namespace math
{
	class Noise2D : public math::Function<double, const Point2D&> { };

	class Noise3D : public math::Function<double, const Point3D&> { };
}