#include "math/vector3d.h"
#include <math.h>

using namespace math;



std::ostream& math::operator <<(std::ostream& out, const Vector3D& v)
{
	return out << "(" << v.x << "," << v.y << "," << v.z << ")";
}

constexpr double math::Vector3D::dot(const Vector3D& v) const noexcept
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3D math::Vector3D::cross(const Vector3D& v) const noexcept
{
	const Vector3D& u = *this;

	double x = u.y * v.z - u.z * v.y;
	double y = -(u.x * v.z - u.z * v.x);
	double z = u.x * v.y - u.y * v.x;

	return Vector3D(x, y, z);
}

constexpr double math::Vector3D::norm_sqr() const noexcept
{
	return dot(*this);
}

double math::Vector3D::norm() const noexcept
{
	return std::sqrt(norm_sqr());
}

void math::Vector3D::normalize() noexcept
{
	*this = normalized();
}

Vector3D math::Vector3D::normalized() const noexcept
{
	return *this / norm();
}

Vector3D& math::Vector3D::operator+=(const Vector3D& v) noexcept
{
	return *this = *this + v;
}

Vector3D& math::Vector3D::operator-=(const Vector3D& v) noexcept
{
	return *this = *this - v;
}

Vector3D& math::Vector3D::operator*=(double factor) noexcept
{
	return *this = *this * factor;
}

Vector3D& math::Vector3D::operator/=(double factor) noexcept
{
	return *this = *this / factor;
}

bool math::Vector3D::is_unit() const noexcept
{
	return norm() == approx(1);
}
