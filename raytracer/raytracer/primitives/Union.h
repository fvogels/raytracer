#pragma once

#include "primitives/Primitive.h"
#include <vector>
#include <memory>

namespace raytracer
{
	class Union : public Primitive
	{
	public:
		virtual bool find_hit(const math::ray&, Hit*) const override;

	private:
		std::vector<std::shared_ptr<const Primitive>> children;
	};
}