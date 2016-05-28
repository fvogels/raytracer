#pragma once

#include "primitives/Primitive.h"
#include "math/point3d.h"

namespace Raytracer
{
	class Plane : public Primitive
	{
	public:
		Plane(const math::point3d& point, const math::vector3d& normal);

		virtual bool find_hit(const math::Ray&, Hit*) const override;

		math::point3d point;
		math::vector3d normal;
	};
}