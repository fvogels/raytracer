#pragma once

#include "primitives/Primitive.h"
#include <vector>
#include <memory>

namespace Raytracer
{
	class Union : public Primitive
	{
	public:
		virtual bool find_hit(const math::Ray&, Hit*) const override;

	private:
		std::vector<std::shared_ptr<const Primitive>> children;
	};
}