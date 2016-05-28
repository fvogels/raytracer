#pragma once

#include "primitives/Primitive.h"
#include "math/point3d.h"

namespace raytracer
{
	class Plane : public Primitive
	{
	public:
		virtual bool find_hit(const math::ray&, Hit*) const override;

	private:
		math::point3d point;
		math::vector3d normal;
	};
}