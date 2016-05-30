#include "rendering/grid-sampler.h"
#include "math/rasterizer.h"

using namespace math;

void Raytracer::GridSampler::sample(const Rectangle2D& rectangle, std::function<void(const Point2D&)> function) const
{
	Rasterizer raster(rectangle, this->columns, this->rows);
	
	for (int y = 0; y != this->rows; ++y)
	{
		for (int x = 0; x != this->columns; ++x)
		{
			auto subrectangle = raster[position(x, y)];

			function(subrectangle.center());
		}
	}
}