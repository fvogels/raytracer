#include "math/vector3d.h"
#include "math/util.h"
#include <math.h>

using namespace math;

Vector3D math::operator +(const Vector3D& u, const Vector3D& v)
{
	double x = u.x + v.x;
	double y = u.y + v.y;
	double z = u.z + v.z;

	return Vector3D(x, y, z);
}

Vector3D math::operator -(const Vector3D& v)
{
	double x = - v.x;
	double y = - v.y;
	double z = - v.z;

	return Vector3D(x, y, z);
}

Vector3D math::operator -(const Vector3D& u, const Vector3D& v)
{
	double x = u.x - v.x;
	double y = u.y - v.y;
	double z = u.z - v.z;

	return Vector3D(x, y, z);
}

Vector3D math::operator *(const Vector3D& v, double factor)
{
	double x = v.x * factor;
	double y = v.y * factor;
	double z = v.z * factor;

	return Vector3D(x, y, z);
}

Vector3D math::operator *(double factor, const Vector3D& v)
{
	return v * factor;
}

Vector3D math::operator /(const Vector3D& v, double factor)
{
	return v * (1.0 / factor);
}

std::ostream& math::operator <<(std::ostream& out, const Vector3D& v)
{
	return out << "(" << v.x << "," << v.y << "," << v.z << ")";
}

double math::Vector3D::dot(const Vector3D& v) const
{
	double result = 0;

	result += x * v.x;
	result += y * v.y;
	result += z * v.z;

	return result;
}

Vector3D math::Vector3D::cross(const Vector3D& v) const
{
	const Vector3D& u = *this;

	double x = u.y * v.z - u.z * v.y;
	double y = -(u.x * v.z - u.z * v.x);
	double z = u.x * v.y - u.y * v.x;

	return Vector3D(x, y, z);
}

double math::Vector3D::norm_sqr() const
{
	return dot(*this);
}

double math::Vector3D::norm() const
{
	return std::sqrt(norm_sqr());
}

void math::Vector3D::normalize()
{
	*this = normalized();
}

Vector3D math::Vector3D::normalized() const
{
	return *this / norm();
}

Vector3D& math::Vector3D::operator+=(const Vector3D& v)
{
	return *this = *this + v;
}

Vector3D& math::Vector3D::operator-=(const Vector3D& v)
{
	return *this = *this - v;
}

Vector3D& math::Vector3D::operator*=(double factor)
{
	return *this = *this * factor;
}

Vector3D& math::Vector3D::operator/=(double factor)
{
	return *this = *this / factor;
}

bool math::Vector3D::is_unit() const
{
	return norm() == approx(1);
}

bool math::Vector3D::is_perpendicular_on(const Vector3D& v) const
{
	return dot(v) == approx(0);
}

bool math::operator ==(const Vector3D& u, const Vector3D& v)
{
	return u.x == v.x && u.y == v.y && u.z == v.z;
}

bool math::operator !=(const Vector3D& u, const Vector3D& v)
{
	return !(u == v);
}