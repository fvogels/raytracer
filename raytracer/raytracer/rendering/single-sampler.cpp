#include "rendering/single-sampler.h"

using namespace math;

void raytracer::SingleSampler::sample(const Rectangle2D& rectangle, std::function<void(const Point2D&)> function) const
{
	function(rectangle.center());
}