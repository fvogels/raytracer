#pragma once

#include "materials/material.h"
#include "math/function.h"
#include "math/point2d.h"

namespace raytracer
{
	namespace materials
	{
		std::shared_ptr<Material> uniform(const imaging::color&);
		std::shared_ptr<Material> pattern2d(math::Function<bool, const math::Point2D&>, const imaging::color&, const imaging::color&);
		std::shared_ptr<Material> horizontal_lines(double thickness, const imaging::color&, const imaging::color&);
		std::shared_ptr<Material> vertical_lines(double thickness, const imaging::color&, const imaging::color&);
		std::shared_ptr<Material> grid(double thickness, const imaging::color&, const imaging::color&);
		std::shared_ptr<Material> checkered(const imaging::color&, const imaging::color&);
		std::shared_ptr<Material> worley(const imaging::color&, const imaging::color&);
	}
}