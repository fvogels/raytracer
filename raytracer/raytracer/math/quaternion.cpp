#include "math/quaternion.h"
#include <assert.h>
#include <math.h>
#include "math/approx.h"

using namespace math;


math::Quaternion::Quaternion(double a, double b, double c, double d)
    : a(a), b(b), c(c), d(d)
{
    // NOP
}

math::Quaternion::Quaternion(const Point3D& p)
    : a(0), b(p.x()), c(p.y()), d(p.z())
{
    // NOP
}

Quaternion math::Quaternion::rotation(Angle angle, const Vector3D& axis)
{
    assert(axis.norm() == approx(1.0));

    double c = cos(angle / 2);
    double s = sin(angle / 2);

    return Quaternion(c, s * axis.x(), s * axis.y(), s * axis.z());
}

Quaternion math::Quaternion::conjugate() const
{
    return Quaternion(a, -b, -c, -d);
}

Point3D math::Quaternion::rotate(const Point3D& p) const
{
    Quaternion q = (*this * Quaternion(p) * this->conjugate());

    assert(q.a == approx(0.0));

    return Point3D(q.b, q.c, q.d);
}

Quaternion math::operator +(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.a + q2.a, q1.b + q2.b, q1.c + q2.c, q1.d + q2.d);
}

Quaternion math::operator -(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.a - q2.a, q1.b - q2.b, q1.c - q2.c, q1.d - q2.d);
}

Quaternion math::operator *(const Quaternion& q, double f)
{
    return Quaternion(q.a * f, q.b * f, q.c * f, q.d * f);
}

Quaternion math::operator *(double f, const Quaternion& q)
{
    return q * f;
}

Quaternion math::operator /(const Quaternion& q, double f)
{
    return q * (1.0 / f);
}

Quaternion math::operator *(const Quaternion& q1, const Quaternion& q2)
{
    const double& a1 = q1.a;
    const double& b1 = q1.b;
    const double& c1 = q1.c;
    const double& d1 = q1.d;
    const double& a2 = q2.a;
    const double& b2 = q2.b;
    const double& c2 = q2.c;
    const double& d2 = q2.d;

    double a = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2;
    double b = a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2;
    double c = a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2;
    double d = a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2;

    return Quaternion(a, b, c, d);
}
