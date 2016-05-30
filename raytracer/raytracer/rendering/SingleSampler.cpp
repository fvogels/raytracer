#include "SingleSampler.h"

using namespace math;

void Raytracer::SingleSampler::sample(const rectangle2d& rectangle, std::function<void(const Point2D&)> function) const
{
	function(rectangle.center());
}