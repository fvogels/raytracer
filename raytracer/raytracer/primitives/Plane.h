#pragma once

#include "primitives/Primitive.h"
#include "math/point3d.h"

namespace Raytracer
{
	class Plane : public Primitive
	{
	public:
		Plane(const math::Point3D& point, const math::vector3d& normal);

		virtual bool find_hit(const math::Ray&, Hit*) const override;

		math::Point3D point;
		math::vector3d normal;
	};
}