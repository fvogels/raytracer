#pragma once

#include "Sampler.h"

namespace Raytracer
{
	class SingleSampler : public Sampler
	{
	public:
		void sample(const math::rectangle2d& rectangle, std::function<void(const math::Point2D&)> function) const override;
	};
}