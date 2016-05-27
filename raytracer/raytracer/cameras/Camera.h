#pragma once

#include "math/ray.h"
#include "math/point2d.h"
#include "math/ray.h"
#include <functional>

namespace raytracer
{
	class Camera
	{
	public:
		virtual math::ray create_ray(const math::point2d&) const = 0;
	};
}