#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
	namespace primitives
	{
		class PlaneXY : public Primitive
		{
		public:
			bool find_hit(const math::Ray&, Hit*) const override;
			std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
		};
	}
}