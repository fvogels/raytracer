#pragma once

#include "primitives/primitive.h"
#include "materials/material3d.h"
#include <memory>

namespace raytracer
{
	class Decorator : public Primitive
	{
	public:
		Decorator(std::shared_ptr<const Material3D>, std::shared_ptr<const Primitive>);

		virtual bool find_hit(const math::Ray&, Hit*) const override;

	private:
		std::shared_ptr<const Material3D> material;
		std::shared_ptr<const Primitive> child;
	};
}