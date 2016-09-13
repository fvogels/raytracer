#include "samplers/stratified-half-jittered-sampler.h"
#include "math/rasterizer.h"
#include <random>

using namespace math;
using namespace raytracer;


namespace
{
    class StratiefiedHalfJitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        StratiefiedHalfJitteredSampler(unsigned rows, unsigned columns)
            : m_rows(rows), m_columns(columns) { }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            Rasterizer raster(rectangle, this->m_columns, this->m_rows);
            std::default_random_engine generator;
            std::uniform_real_distribution<double> distribution(0.25, 0.75);

            for (unsigned y = 0; y != this->m_rows; ++y)
            {
                for (unsigned x = 0; x != this->m_columns; ++x)
                {
                    auto subrectangle = raster[Position2D(x, y)];
                    double rx = distribution(generator);
                    double ry = distribution(generator);
                    Point2D p = subrectangle.from_relative(Point2D(rx, ry));

                    function(p);
                }
            }
        }

    private:
        unsigned m_rows, m_columns;
    };
}

Sampler raytracer::samplers::stratified_half_jittered(unsigned rows, unsigned columns)
{
    return Sampler(std::make_shared<StratiefiedHalfJitteredSampler>(rows, columns));
}
