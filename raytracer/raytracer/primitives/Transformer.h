#pragma once

#include "primitives/Primitive.h"
#include "math/transformation.h"
#include <memory>

namespace raytracer
{
	class Transformer : public Primitive
	{
	public:
		Transformer(const math::transformation& transformer, std::shared_ptr<const Primitive> transformee)
			: transformer(transformer), transformee(transformee) { }

		virtual bool find_hit(const math::ray&, Hit*) const override;

	private:
		math::transformation transformer;
		std::shared_ptr<const Primitive> transformee;
	};
}