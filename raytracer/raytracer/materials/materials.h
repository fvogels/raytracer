#pragma once

#include "materials/material.h"
#include "math/function.h"
#include "math/point2d.h"

namespace raytracer
{
	namespace materials
	{
		Material uniform(const imaging::color&);
		Material pattern2d(math::Function<bool, const math::Point2D&>, const imaging::color&, const imaging::color&);
		Material horizontal_lines(double thickness, const imaging::color&, const imaging::color&);
		Material vertical_lines(double thickness, const imaging::color&, const imaging::color&);
		Material grid(double thickness, const imaging::color&, const imaging::color&);
		Material checkered(const imaging::color&, const imaging::color&);
		Material worley(const imaging::color&, const imaging::color&);
	}
}