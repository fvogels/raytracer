#pragma once

#include "primitives/Primitive.h"
#include "math/transformation.h"
#include <memory>

namespace Raytracer
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