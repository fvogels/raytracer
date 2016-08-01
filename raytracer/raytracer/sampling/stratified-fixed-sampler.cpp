#include "sampling/stratified-fixed-sampler.h"
#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


namespace
{
    class StratiefiedFixedSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        StratiefiedFixedSampler(unsigned rows, unsigned columns)
            : m_rows(rows), m_columns(columns) { }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
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

    private:
        unsigned m_rows, m_columns;
    };
}

Sampler raytracer::samplers::stratified_fixed(unsigned rows, unsigned columns)
{
    return Sampler(std::make_shared<StratiefiedFixedSampler>(rows, columns));
}