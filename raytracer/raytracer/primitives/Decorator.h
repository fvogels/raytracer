#pragma once

#include "primitives/Primitive.h"
#include "materials/Material3D.h"
#include <memory>

namespace raytracer
{
	class Decorator : public Primitive
	{
	public:
		Decorator(std::shared_ptr<const Material3D>, std::shared_ptr<const Primitive>);

		virtual bool find_hit(const math::ray&, Hit*) const override;

	private:
		std::shared_ptr<const Material3D> material;
		std::shared_ptr<const Primitive> child;
	};
}