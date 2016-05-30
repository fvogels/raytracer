#pragma once

#include "math/rectangle2d.h"
#include <functional>

namespace Raytracer
{
	class Sampler
	{
	public:
		virtual void sample(const math::rectangle2d& rectangle, std::function<void(const math::Point2D&)> function) const = 0;
	};
}