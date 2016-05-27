#pragma once

#include "cameras/Camera.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include <memory>

namespace raytracer
{
	std::shared_ptr<Camera> createPerspectiveCamera(
		const math::point3d& eye,
		const math::point3d& look_at,
		const math::vector3d& up,
		double distance,
		double aspect_ratio);
}