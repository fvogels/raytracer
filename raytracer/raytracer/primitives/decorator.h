#pragma once

#include "primitives/primitive.h"
#include "materials/material.h"
#include <memory>

namespace raytracer
{
	namespace primitives
	{
		class Decorator : public Primitive
		{
		public:
			Decorator(std::shared_ptr<Material>, std::shared_ptr<Primitive>);

			virtual bool find_hit(const math::Ray&, Hit*) const override;

		private:
			std::shared_ptr<Material> material;
			std::shared_ptr<Primitive> child;
		};
	}
}