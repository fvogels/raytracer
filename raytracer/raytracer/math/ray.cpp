#include "math/ray.h"

using namespace math;

ray math::ray::transform(const matrix4d& m) const
{
	return ray(m * origin, m * direction);
}