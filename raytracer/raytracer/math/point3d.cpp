#include "math/point3d.h"

using namespace math;

Point3D math::operator +(const Point3D& p, const Vector3D& v)
{
	double x = p.x + v.x;
	double y = p.y + v.y;
	double z = p.z + v.z;

	return Point3D(x, y, z);
}

Point3D math::operator +(const Vector3D& v, const Point3D& p)
{
	return p + v;
}

Vector3D math::operator -(const Point3D& p, const Point3D& q)
{
	double x = p.x - q.x;
	double y = p.y - q.y;
	double z = p.z - q.z;

	return Vector3D(x, y, z);
}

Point3D math::operator -(const Point3D& p, const Vector3D& v)
{
	double x = p.x - v.x;
	double y = p.y - v.y;
	double z = p.z - v.z;

	return Point3D(x, y, z);
}

double math::distance(const Point3D& p, const Point3D& q)
{
	return (q - p).norm();
}
