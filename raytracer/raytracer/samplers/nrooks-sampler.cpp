#include "samplers/nrooks-sampler.h"
#include "math/rasterizer.h"
#include <random>
#include <algorithm>

using namespace math;
using namespace raytracer;


namespace
{
    class NRooksSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        NRooksSampler(unsigned sample_count)
            : m_sample_count(sample_count), m_distribution(0, 1)
        {
            // NOP
        }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            Rasterizer raster(rectangle, this->m_sample_count, this->m_sample_count);

            std::vector<unsigned> columns(m_sample_count);
            for (unsigned i = 0; i != m_sample_count; ++i)
            {
                columns[i] = i;
            }

            std::shuffle(columns.begin(), columns.end(), m_generator);

            for (unsigned y = 0; y != this->m_sample_count; ++y)
            {
                unsigned x = columns[y];
                
                auto subrectangle = raster[Position2D(x, y)];
                double rx = m_distribution(m_generator);
                double ry = m_distribution(m_generator);
                Point2D p = subrectangle.from_relative(Point2D(rx, ry));

                function(p);
            }
        }

    private:
        unsigned m_sample_count;

        mutable std::default_random_engine m_generator;

        std::uniform_real_distribution<double> m_distribution;
    };
}

Sampler raytracer::samplers::nrooks(unsigned sample_count)
{
    return Sampler(std::make_shared<NRooksSampler>(sample_count));
}