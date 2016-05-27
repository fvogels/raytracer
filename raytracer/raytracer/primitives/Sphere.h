#pragma once

#include "primitives/Primitive.h"

namespace raytracer
{
	class Sphere : public Primitive
	{
	public:
		virtual bool find_hit(const math::ray&, Hit*) const override;
	};
}