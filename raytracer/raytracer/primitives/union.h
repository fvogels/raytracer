#pragma once

#include "primitives/primitive.h"
#include <vector>
#include <memory>

namespace raytracer
{
	class Union : public Primitive
	{
	public:
		Union(std::vector<std::shared_ptr<Primitive>>&);

		virtual bool find_hit(const math::Ray&, Hit*) const override;

	private:
		std::vector<std::shared_ptr<Primitive>> children;
	};
}