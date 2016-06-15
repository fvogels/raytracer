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
		virtual math::Ray create_Ray(const math::Point2D&) const = 0;
	};
}