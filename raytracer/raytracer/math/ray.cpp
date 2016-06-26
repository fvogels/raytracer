#include "math/ray.h"

using namespace math;

Ray math::Ray::transform(const Matrix4D& m) const
{
	auto transformed_origin = m * origin;
	auto transformed_direction = m * direction;

	return Ray(transformed_origin, transformed_direction);
}

std::ostream& math::operator <<(std::ostream& out, const Ray& ray)
{
    return out << "RAY[" << ray.origin << " : " << ray.direction << "]";
}