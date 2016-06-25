#pragma once

#include "cameras/camera.h"
#include "math/vector3d.h"
#include "math/point2d.h"
#include "math/point3d.h"
#include "math/rectangle3d.h"

#include <memory>

namespace raytracer
{
	namespace cameras
	{
		class FisheyeCamera : public DisplacableCamera
		{
		public:
			FisheyeCamera(const math::Matrix4D&);

		protected:
			math::Ray create_untransformed_ray(const math::Point2D& point) const override;
		};
	}
}