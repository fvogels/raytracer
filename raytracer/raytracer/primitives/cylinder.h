#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
	namespace primitives
	{
		class Cylinder : public Primitive
		{
		public:
			virtual bool find_hit(const math::Ray&, Hit*) const override;
		};
	}
}