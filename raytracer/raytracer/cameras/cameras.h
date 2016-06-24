#pragma once

#include "cameras/camera.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include <memory>


namespace raytracer
{
	namespace cameras
	{
		std::shared_ptr<Camera> orthographic(
			const math::Point3D& eye,
			const math::Point3D& look_at,
			const math::Vector3D& up,
			double distance,
			double aspect_ratio);

		std::shared_ptr<Camera> perspective(
			const math::Point3D& eye,
			const math::Point3D& look_at,
			const math::Vector3D& up,
			double distance,
			double aspect_ratio);

		std::shared_ptr<Camera> fisheye();
	}
}