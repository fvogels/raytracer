#pragma once

#include "math/ray.h"
#include "math/Point2D.h"
#include "math/ray.h"
#include <functional>

namespace Raytracer
{
	class Camera
	{
	public:
		virtual math::Ray create_Ray(const math::Point2D&) const = 0;
	};
}