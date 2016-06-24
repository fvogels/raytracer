#pragma once

#include "math/ray.h"
#include "math/point2d.h"
#include "math/ray.h"
#include "math/matrix4d.h"
#include <functional>

namespace raytracer
{
	class Camera
	{
	public:
		virtual math::Ray create_ray(const math::Point2D&) const = 0;
	};

	class DisplacableCamera : public Camera
	{
	public:
		math::Ray create_ray(const math::Point2D& p) const
		{
			return create_untransformed_ray(p).transform(m_transformation);
		}

	protected:
		DisplacableCamera(math::Matrix4D transformation)
			: m_transformation(transformation)
		{
			// NOP
		}

		virtual math::Ray create_untransformed_ray(const math::Point2D&) const = 0;

	private:
		math::Matrix4D m_transformation;
	};
}