#pragma once

#include "primitives/Hit.h"
#include "math/ray.h"

namespace raytracer
{
	class Primitive
	{
	public:
		virtual bool find_hit(const math::ray&, Hit*) const = 0;
	};
}