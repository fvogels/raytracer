#pragma once

#include "primitives/Primitive.h"

namespace Raytracer
{
	class Sphere : public Primitive
	{
	public:
		virtual bool find_hit(const math::Ray&, Hit*) const override;
	};
}