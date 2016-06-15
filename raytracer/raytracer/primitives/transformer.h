#pragma once

#include "primitives/primitive.h"
#include "math/transformation.h"
#include <memory>

namespace raytracer
{
	class Transformer : public Primitive
	{
	public:
		Transformer(const math::Transformation& transformer, std::shared_ptr<const Primitive> transformee)
			: transformer(transformer), transformee(transformee) { }

		virtual bool find_hit(const math::Ray&, Hit*) const override;

	private:
		math::Transformation transformer;
		std::shared_ptr<const Primitive> transformee;
	};
}