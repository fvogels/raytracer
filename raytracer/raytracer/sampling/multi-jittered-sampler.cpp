#include "sampling/multi-jittered-sampler.h"
#include "math/rasterizer.h"
#include <random>
#include <algorithm>

using namespace math;
using namespace raytracer;


namespace
{
    class MultiJitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        MultiJitteredSampler(unsigned sqrt_sample_count)
            : m_sqrt_sample_count(sqrt_sample_count) { }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            Rasterizer raster(rectangle, this->m_sqrt_sample_count * this->m_sqrt_sample_count, this->m_sqrt_sample_count * this->m_sqrt_sample_count);
            std::default_random_engine generator;
            std::uniform_real_distribution<double> distribution(0, 1);

            std::vector<unsigned> indices(m_sqrt_sample_count * m_sqrt_sample_count);
            for (unsigned i = 0; i != m_sqrt_sample_count * m_sqrt_sample_count; ++i)
            {
                indices[i] = i;
            }

            std::shuffle(indices.begin(), indices.end(), generator);

            for (unsigned x = 0; x != this->m_sqrt_sample_count; ++x)
            {
                for (unsigned y = 0; y != this->m_sqrt_sample_count; ++y)
                {
                    unsigned index = indices[x + y * m_sqrt_sample_count];
                    unsigned sx = index % m_sqrt_sample_count;
                    unsigned sy = index / m_sqrt_sample_count;
                    unsigned cx = x * m_sqrt_sample_count + sx;
                    unsigned cy = y * m_sqrt_sample_count + sy;
                    auto subrectangle = raster[Position(cx, cy)];

                    double rx = distribution(generator);
                    double ry = distribution(generator);
                    Point2D p = subrectangle.from_relative(Point2D(rx, ry));

                    function(p);
                }
            }
        }

    private:
        unsigned m_sqrt_sample_count;
    };
}

Sampler raytracer::samplers::multi_jittered(unsigned sqrt_sample_count)
{
    return Sampler(std::make_shared<MultiJitteredSampler>(sqrt_sample_count));
}