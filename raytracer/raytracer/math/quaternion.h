#pragma once

#include "math/point3d.h"
#include "math/vector3d.h"


namespace math
{
    class Quaternion final
    {
    public:
        double a, b, c, d;

        Quaternion(double a, double b, double c, double d);
        explicit Quaternion(const Point3D& p);
        Quaternion(Angle angle, const Vector3D& v);

        Quaternion conjugate() const;

        Point3D rotate(const Point3D& p) const;
    };

    Quaternion operator +(const Quaternion& q1, const Quaternion& q2);
    Quaternion operator -(const Quaternion& q1, const Quaternion& q2);
    Quaternion operator *(const Quaternion& q, double f);
    Quaternion operator *(double f, const Quaternion& q);
    Quaternion operator *(const Quaternion& q1, const Quaternion& q2);
    Quaternion operator /(const Quaternion& q1, double f);

    inline Quaternion& operator +=(Quaternion& q1, const Quaternion& q2) { return q1 = q1 + q2; }
    inline Quaternion& operator -=(Quaternion& q1, const Quaternion& q2) { return q1 = q1 - q2; }
    inline Quaternion& operator *=(Quaternion& q1, double f) { return q1 = q1 * f; }
    inline Quaternion& operator /=(Quaternion& q1, double f) { return q1 = q1 / f; }
}