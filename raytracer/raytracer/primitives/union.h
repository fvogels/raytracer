#pragma once

#include "primitives/primitive.h"
#include <vector>
#include <memory>

namespace raytracer
{
	namespace primitives
	{
		class Union : public Primitive
		{
		public:
			Union(std::vector<std::shared_ptr<Primitive>>&);

			bool find_hit(const math::Ray&, Hit*) const override;
			std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;

		private:
			std::vector<std::shared_ptr<Primitive>> children;
		};
	}
}