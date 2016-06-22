#include "math/point3d.h"

using namespace math;


double math::distance(const Point3D& p, const Point3D& q) noexcept
{
	return (q - p).norm();
}

std::ostream& math::operator <<(std::ostream& out, const Point3D& p)
{
	return out << "(" << p.x << "," << p.y << "," << p.z << ")";
}