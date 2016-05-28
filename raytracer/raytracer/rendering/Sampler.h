#pragma once

#include "math/rectangle2d.h"
#include <functional>

namespace Raytracer
{
	class Sampler
	{
	public:
		virtual void sample(const math::rectangle2d& rectangle, std::function<void(const math::point2d&)> function) const = 0;
	};
}