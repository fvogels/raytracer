#pragma once

#include "math/rectangle2d.h"
#include <functional>

namespace raytracer
{
	class Sampler
	{
	public:
		virtual void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const = 0;
	};
}