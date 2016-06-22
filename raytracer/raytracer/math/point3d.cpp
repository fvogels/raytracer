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

Point3D math::operator +(const Point3D& p, const Vector3D& v) noexcept
{
	return Point3D(p.x + v.x, p.y + v.y, p.z + v.z);
}

Point3D math::operator +(const Vector3D& v, const Point3D& p) noexcept
{
	return p + v;
}

Vector3D math::operator -(const Point3D& p, const Point3D& q) noexcept
{
	return Vector3D(p.x - q.x, p.y - q.y, p.z - q.z);
}

Point3D math::operator -(const Point3D& p, const Vector3D& v) noexcept
{
	return Point3D(p.x - v.x, p.y - v.y, p.z - v.z);
}

bool math::operator ==(const Point3D& p, const Point3D& q) noexcept
{
	return p.x == q.x && p.y == q.y && p.z == q.z;
}

bool math::operator !=(const Point3D& p, const Point3D& q) noexcept
{
	return !(p == q);
}