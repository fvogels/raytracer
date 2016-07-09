#include "sampling/single-sampler.h"

using namespace math;

void raytracer::samplers::_private_::SingleSampler::sample(const Rectangle2D& rectangle, std::function<void(const Point2D&)> function) const
{
    function(rectangle.center());
}