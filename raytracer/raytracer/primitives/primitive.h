#pragma once

#include "primitives/hit.h"
#include "math/ray.h"
#include <vector>
#include <memory>

namespace raytracer
{
	namespace primitives
	{
		struct Context
		{
			std::shared_ptr<MaterialImplementation> material;
		};

		class Primitive
		{
		public:
			virtual bool find_hit(const math::Ray&, Hit*) const = 0;
			virtual std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const = 0;
		};
	}
}