#include "point3d.h"

using namespace math;

vector3d math::operator +(const point3d& p, const vector3d& v)
{
	double x = p.x + v.x;
	double y = p.y + v.y;
	double z = p.z + v.z;

	return vector3d(x, y, z);
}

vector3d math::operator +(const vector3d& v, const point3d& p)
{
	return p + v;
}

vector3d math::operator -(const point3d& p, const point3d& q)
{
	double x = p.x - q.x;
	double y = p.y - q.y;
	double z = p.z - q.z;

	return vector3d(x, y, z);
}