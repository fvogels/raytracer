#include "math/point3D.h"

using namespace math;

Point3D math::operator +(const Point3D& p, const vector3d& v)
{
	double x = p.x + v.x;
	double y = p.y + v.y;
	double z = p.z + v.z;

	return Point3D(x, y, z);
}

Point3D math::operator +(const vector3d& v, const Point3D& p)
{
	return p + v;
}

vector3d math::operator -(const Point3D& p, const Point3D& q)
{
	double x = p.x - q.x;
	double y = p.y - q.y;
	double z = p.z - q.z;

	return vector3d(x, y, z);
}

Point3D math::operator -(const Point3D& p, const vector3d& v)
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
