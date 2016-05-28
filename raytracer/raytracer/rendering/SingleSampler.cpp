#include "SingleSampler.h"

using namespace math;

void Raytracer::SingleSampler::sample(const rectangle2d& rectangle, std::function<void(const point2d&)> function) const
{
	function(rectangle.center());
}