#pragma once

#include "math/ray.h"
#include <functional>

namespace raytracer
{
	class Camera
	{
	public:
		virtual void each_ray(std::function<void(const math::ray&)>) const = 0;
	};
}