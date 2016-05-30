#pragma once

#include "math/rectangle2D.h"
#include <functional>

namespace Raytracer
{
	class Sampler
	{
	public:
		virtual void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const = 0;
	};
}