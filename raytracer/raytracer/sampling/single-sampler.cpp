#include "sampling/single-sampler.h"

using namespace math;
using namespace raytracer;


void raytracer::samplers::_private_::SingleSampler::sample(const Rectangle2D& rectangle, std::function<void(const Point2D&)> function) const
{
    function(rectangle.center());
}

Sampler raytracer::samplers::single()
{
    return Sampler(std::make_shared<_private_::SingleSampler>());
}