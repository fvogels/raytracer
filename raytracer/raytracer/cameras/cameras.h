#pragma once

#include "cameras/camera.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include <memory>


namespace raytracer
{
	namespace cameras
	{
		math::Matrix4D create_transformation(const math::Point3D&, const math::Point3D&, const math::Vector3D&);

		std::shared_ptr<Camera> orthographic(
			const math::Point3D& eye,
			const math::Point3D& look_at,
			const math::Vector3D& up,
			double window_width,
			double aspect_ratio);

		std::shared_ptr<Camera> perspective(
			const math::Point3D& eye,
			const math::Point3D& look_at,
			const math::Vector3D& up,
			double distance,
			double aspect_ratio);

		std::shared_ptr<Camera> fisheye(
			const math::Point3D& eye,
			const math::Point3D& look_at,
			const math::Vector3D& up,
			const math::Angle& horizontal_angle,
			const math::Angle& vertical_angle);
	}
}