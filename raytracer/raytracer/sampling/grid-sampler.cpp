#include "sampling/grid-sampler.h"
#include "math/rasterizer.h"

using namespace math;
using namespace raytracer::samplers;


void raytracer::samplers::_private_::GridSampler::sample(const Rectangle2D& rectangle, std::function<void(const Point2D&)> function) const
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

Sampler raytracer::samplers::grid(int rows, int columns)
{
    return Sampler(std::make_shared<_private_::GridSampler>(rows, columns));
}