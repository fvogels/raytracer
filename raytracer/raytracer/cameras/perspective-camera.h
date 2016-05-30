#pragma once

#include "cameras/camera.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include <memory>

namespace Raytracer
{
	std::shared_ptr<Camera> create_perspective_camera(
		const math::Point3D& eye,
		const math::Point3D& look_at,
		const math::Vector3D& up,
		double distance,
		double aspect_ratio);
}