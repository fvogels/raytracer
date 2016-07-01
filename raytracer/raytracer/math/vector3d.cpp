#include "math/vector3d.h"
#include <math.h>

using namespace math;


std::ostream& math::operator <<(std::ostream& out, const Vector3D& v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << ")";
}

double math::Vector3D::dot(const Vector3D& v) const noexcept
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

double math::Vector3D::norm_sqr() const noexcept
{
    return dot(*this);
}

double math::Vector3D::norm() const noexcept
{
    return sqrt(norm_sqr());
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
    return norm() == approx(1.0);
}

Vector3D math::operator +(const Vector3D& u, const Vector3D& v) noexcept
{
    return Vector3D(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector3D math::operator -(const Vector3D& v) noexcept
{
    return Vector3D(-v.x, -v.y, -v.z);
}

Vector3D math::operator -(const Vector3D& u, const Vector3D& v) noexcept
{
    return Vector3D(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vector3D math::operator *(const Vector3D& v, double factor) noexcept
{
    return Vector3D(v.x * factor, v.y * factor, v.z * factor);
}

Vector3D math::operator *(double factor, const Vector3D& v) noexcept
{
    return v * factor;
}

Vector3D math::operator /(const Vector3D& v, double factor) noexcept
{
    return v * (1.0 / factor);
}

bool math::operator ==(const Vector3D& u, const Vector3D& v) noexcept
{
    return u.x == v.x && u.y == v.y && u.z == v.z;
}

bool math::operator !=(const Vector3D& u, const Vector3D& v) noexcept
{
    return !(u == v);
}

Vector3D math::Vector3D::reflect_by(const Vector3D& n) const
{
    const Vector3D& v = *this;

    return v - 2 * v.dot(n) * n;
}
