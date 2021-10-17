#include "samplers/random-sampler.h"
#include "math/rasterizer.h"
#include <random>

using namespace math;
using namespace raytracer;


namespace
{
    class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        RandomSampler(unsigned sample_count)
            : m_sample_count(sample_count), m_distribution(0, 1)
        {
            // NOP
        }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            for (unsigned i = 0; i != m_sample_count; ++i)
            {
                double x = m_distribution(generator);
                double y = m_distribution(generator);
                Point2D sample = rectangle.from_relative(Point2D(x, y));

                function(sample);
            }
        }

    private:
        unsigned m_sample_count;

        mutable std::default_random_engine generator;

        std::uniform_real_distribution<double> m_distribution;
    };
}

Sampler raytracer::samplers::random(unsigned sample_count)
{
    return Sampler(std::make_shared<RandomSampler>(sample_count));
}