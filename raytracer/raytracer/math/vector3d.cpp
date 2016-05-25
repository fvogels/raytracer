#include "math/vector3d.h"

using namespace math;

vector3d math::operator +(const vector3d& u, const vector3d& v)
{
	double x = u.x + v.x;
	double y = u.y + v.y;
	double z = u.z + v.z;

	return vector3d(x, y, z);
}

vector3d math::operator -(const vector3d& u, const vector3d& v)
{
	double x = u.x - v.x;
	double y = u.y - v.y;
	double z = u.z - v.z;

	return vector3d(x, y, z);
}

vector3d math::operator *(const vector3d& v, double factor)
{
	double x = v.x * factor;
	double y = v.y * factor;
	double z = v.z * factor;

	return vector3d(x, y, z);
}

vector3d math::operator *(double factor, const vector3d& v)
{
	return v * factor;
}

vector3d math::operator /(const vector3d& v, double factor)
{
	return v * (1.0 / factor);
}

std::ostream& math::operator <<(std::ostream& out, const vector3d& v)
{
	return out << "(" << v.x << "," << v.y << "," << v.z << ")";
}