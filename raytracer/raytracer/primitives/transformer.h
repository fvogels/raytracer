#pragma once

#include "primitives/primitive.h"
#include "math/transformation.h"
#include <memory>

namespace raytracer
{
	namespace primitives
	{
		class Transformer : public Primitive
		{
		public:
			Transformer(const math::Transformation& transformer, std::shared_ptr<const Primitive> transformee)
				: transformer(transformer), transformee(transformee) { }

			bool find_hit(const math::Ray&, Hit*) const override;
			std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;

		private:
			math::Transformation transformer;
			std::shared_ptr<const Primitive> transformee;
		};
	}
}