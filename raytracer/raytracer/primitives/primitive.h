#pragma once

#include "primitives/hit.h"
#include "math/ray.h"

namespace Raytracer
{
	class Primitive
	{
	public:
		virtual bool find_hit(const math::Ray&, Hit*) const = 0;
	};
}