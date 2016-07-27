#include "sampling/grid-sampler.h"
#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


void raytracer::samplers::_private_::GridSampler::sample(const Rectangle2D& rectangle, std::function<void(const Point2D&)> function) const
{
    Rasterizer raster(rectangle, this->m_columns, this->m_rows);
    
    for (int y = 0; y != this->m_rows; ++y)
    {
        for (int x = 0; x != this->m_columns; ++x)
        {
            auto subrectangle = raster[Position(x, y)];

            function(subrectangle.center());
        }
    }
}

Sampler raytracer::samplers::grid(unsigned rows, unsigned columns)
{
    return Sampler(std::make_shared<_private_::GridSampler>(rows, columns));
}