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
		class OrthographicCamera : public Camera
		{
		public:
			OrthographicCamera(const math::Rectangle3D&, const math::Rectangle3D&);

			math::Ray create_ray(const math::Point2D& point) const override;

		private:
			math::Rectangle3D m_eye_window;
			math::Rectangle3D m_view_window;
		};
	}
}