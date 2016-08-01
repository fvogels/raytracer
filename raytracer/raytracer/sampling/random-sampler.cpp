#include "sampling/random-sampler.h"
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
            : m_sample_count(sample_count) { }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            std::default_random_engine generator;
            std::uniform_real_distribution<double> distribution(0, 1);

            for (unsigned i = 0; i != m_sample_count; ++i)
            {
                double x = distribution(generator);
                double y = distribution(generator);
                
                function(rectangle.from_relative(Point2D(x, y)));
            }
        }

    private:
        unsigned m_sample_count;
    };
}

Sampler raytracer::samplers::random(unsigned sample_count)
{
    return Sampler(std::make_shared<RandomSampler>(sample_count));
}