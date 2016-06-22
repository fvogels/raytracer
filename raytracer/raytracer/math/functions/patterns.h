#pragma once

#include "math/function.h"
#include "math/point2d.h"


namespace math
{
	namespace functions
	{
		math::Function<bool, const Point2D&> checkerboard();
		math::Function<bool, const Point2D&> horizontal_lines(double thickness = 0.1);
		math::Function<bool, const Point2D&> vertical_lines(double thickness = 0.1);
	}
}