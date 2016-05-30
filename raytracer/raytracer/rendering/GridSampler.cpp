#include "GridSampler.h"
#include "math/rasteriser.h"

using namespace math;

void Raytracer::GridSampler::sample(const rectangle2d& rectangle, std::function<void(const Point2D&)> function) const
{
	rasteriser raster(rectangle, this->columns, this->rows);
	
	for (int y = 0; y != this->rows; ++y)
	{
		for (int x = 0; x != this->columns; ++x)
		{
			auto subrectangle = raster[position(x, y)];

			function(subrectangle.center());
		}
	}
}