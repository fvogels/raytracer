#pragma once

#include "primitives/primitive.h"
#include <vector>
#include <memory>

namespace raytracer
{
	namespace primitives
	{
		class Intersection : public PrimitiveImplementation
		{
		public:
			Intersection(Primitive, Primitive);

			bool find_hit(const math::Ray&, Hit*) const override;
			std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;

		private:
			Primitive m_first;
			Primitive m_second;
		};
	}
}