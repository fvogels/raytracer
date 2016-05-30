#include "rendering/single-sampler.h"

using namespace math;

void Raytracer::SingleSampler::sample(const Rectangle2D& rectangle, std::function<void(const Point2D&)> function) const
{
	function(rectangle.center());
}