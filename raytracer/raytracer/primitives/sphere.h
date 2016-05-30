#pragma once

#include "primitives/primitive.h"

namespace Raytracer
{
	class Sphere : public Primitive
	{
	public:
		virtual bool find_hit(const math::Ray&, Hit*) const override;
	};
}