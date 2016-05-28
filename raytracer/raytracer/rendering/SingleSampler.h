#pragma once

#include "Sampler.h"

namespace Raytracer
{
	class SingleSampler : public Sampler
	{
	public:
		void sample(const math::rectangle2d& rectangle, std::function<void(const math::point2d&)> function) const override;
	};
}