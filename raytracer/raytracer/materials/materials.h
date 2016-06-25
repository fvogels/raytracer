#pragma once

#include "materials/material.h"
#include "math/function.h"
#include "math/point2d.h"

namespace raytracer
{
	namespace materials
	{
		Material uniform(const imaging::color&, const imaging::color&, double);
		Material pattern2d(math::Function<bool, const math::Point2D&>, Material, Material);
		Material horizontal_lines(double thickness, Material, Material);
		Material vertical_lines(double thickness, Material, Material);
		Material grid(double thickness, Material, Material);
		Material checkered(Material, Material);
		// Material worley(const imaging::color&, const imaging::color&);
	}
}