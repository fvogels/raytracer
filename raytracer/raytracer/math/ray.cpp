#include "math/ray.h"

using namespace math;

Ray math::Ray::transform(const matrix4d& m) const
{
	auto transformed_origin = m * origin;
	auto transformed_direction = m * direction;

	return Ray(transformed_origin, transformed_direction);
}