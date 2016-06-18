#pragma once

#include "primitives/primitive.h"
#include "math/point3d.h"

namespace raytracer
{
	namespace primitives
	{
		class Plane : public Primitive
		{
		public:
			Plane(const math::Point3D& point, const math::Vector3D& normal, const math::Vector3D& u);

			virtual bool find_hit(const math::Ray&, Hit*) const override;

			math::Point3D point;
			math::Vector3D normal;
			math::Vector3D u, v;
		};
	}
}