#pragma once

#include "materials/material.h"
#include "math/function.h"
#include "math/point2d.h"

namespace raytracer
{
	namespace materials
	{
		std::shared_ptr<Material> uniform(const color&);
		std::shared_ptr<Material> pattern2d(math::Function<bool, const math::Point2D&>, const color&, const color&);
		std::shared_ptr<Material> horizontal_lines(double thickness, const color&, const color&);
		std::shared_ptr<Material> vertical_lines(double thickness, const color&, const color&);
		std::shared_ptr<Material> grid(double thickness, const color&, const color&);
		std::shared_ptr<Material> checkered(const color&, const color&);
		std::shared_ptr<Material> worley(const color&, const color&);
	}
}