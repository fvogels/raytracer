#include "math/vector3d.h"
#include "math/util.h"
#include <math.h>

using namespace math;

vector3d math::operator +(const vector3d& u, const vector3d& v)
{
	double x = u.x + v.x;
	double y = u.y + v.y;
	double z = u.z + v.z;

	return vector3d(x, y, z);
}

vector3d math::operator -(const vector3d& v)
{
	double x = - v.x;
	double y = - v.y;
	double z = - v.z;

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

double math::vector3d::dot(const vector3d& v) const
{
	double result = 0;

	result += x * v.x;
	result += y * v.y;
	result += z * v.z;

	return result;
}

vector3d math::vector3d::cross(const vector3d& v) const
{
	double x = y * v.z - z * v.y;
	double y = -(x * v.z - z * v.x);
	double z = x * v.y - y * v.x;

	return vector3d(x, y, z);
}

double math::vector3d::norm_sqr() const
{
	return dot(*this);
}

double math::vector3d::norm() const
{
	return std::sqrt(norm_sqr());
}

void math::vector3d::normalize()
{
	*this = normalized();
}

vector3d math::vector3d::normalized() const
{
	return *this / norm();
}

vector3d& math::vector3d::operator+=(const vector3d& v)
{
	return *this = *this + v;
}

vector3d& math::vector3d::operator-=(const vector3d& v)
{
	return *this = *this - v;
}

vector3d& math::vector3d::operator*=(double factor)
{
	return *this = *this * factor;
}

vector3d& math::vector3d::operator/=(double factor)
{
	return *this = *this / factor;
}

bool math::vector3d::is_unit() const
{
	return norm() == approx(1);
}

bool math::vector3d::is_perpendicular_on(const vector3d& v) const
{
	return dot(v) == approx(0);
}