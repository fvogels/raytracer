#pragma once

#include "primitives/hit.h"
#include "math/ray.h"

namespace raytracer
{
	namespace primitives
	{
		class Primitive
		{
		public:
			virtual bool find_hit(const math::Ray&, Hit*) const = 0;
		};
	}
}