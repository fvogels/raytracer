#pragma once

#include "math/point3d.h"
#include "math/function.h"


namespace math
{
	class Noise3D : public math::Function<double, const Point3D&> { };
}