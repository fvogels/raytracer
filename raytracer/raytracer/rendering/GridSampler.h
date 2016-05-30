#pragma once

#include "Sampler.h"

namespace Raytracer
{
	class GridSampler : public Sampler
	{
	public:
		GridSampler(int rows, int columns)
			: rows(rows), columns(columns) { }

		void sample(const math::rectangle2d& rectangle, std::function<void(const math::Point2D&)> function) const override;

	private:
		int rows, columns;
	};
}