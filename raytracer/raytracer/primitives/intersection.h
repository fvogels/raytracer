#pragma once

#include "primitives/primitive.h"
#include <vector>
#include <memory>

namespace raytracer
{
	namespace primitives
	{
		class Intersection : public Primitive
		{
		public:
			Intersection(std::shared_ptr<Primitive>, std::shared_ptr<Primitive>);

			bool find_hit(const math::Ray&, Hit*) const override;
			std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;

		private:
			std::shared_ptr<Primitive> m_first;
			std::shared_ptr<Primitive> m_second;
		};
	}
}