#include "math/ray.h"

using namespace math;

ray math::ray::transform(const matrix4d& m) const
{
	auto transformed_origin = m * origin;
	auto transformed_direction = m * direction;

	return ray(transformed_origin, transformed_direction);
}