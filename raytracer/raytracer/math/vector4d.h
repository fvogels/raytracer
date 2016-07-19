#pragma once

#include "math/approx.h"
#include "math/angle.h"
#include <iostream>


namespace math
{
    struct Vector4D final
    {
        double x, y, z, w;

        Vector4D(double x, double y, double z, double w) noexcept
            : x(x), y(y), z(z), w(w) { }

        Vector4D(double r, math::Angle alpha, math::Angle beta, math::Angle gamma)
            : x(r * cos(alpha))
            , y(r * sin(alpha) * cos(alpha))
            , z(r * sin(alpha) * sin(beta) * cos(gamma))
            , w(r * sin(alpha) * sin(beta) * sin(gamma)) { }

        Vector4D() noexcept
            : x(0), y(0), z(0), w(0) { }

        Vector4D(const Vector4D&) noexcept = default;

        static Vector4D zero() noexcept { return Vector4D(0, 0, 0, 0); }
        static Vector4D x_axis() noexcept { return Vector4D(1, 0, 0, 0); }
        static Vector4D y_axis() noexcept { return Vector4D(0, 1, 0, 0); }
        static Vector4D z_axis() noexcept { return Vector4D(0, 0, 1, 0); }
        static Vector4D w_axis() noexcept { return Vector4D(0, 0, 0, 1); }

        Vector4D& operator =(const Vector4D&) noexcept = default;

        double dot(const Vector4D&) const noexcept;

        double norm_sqr() const noexcept;
        double norm() const noexcept;
        void normalize() noexcept;
        Vector4D normalized() const noexcept;
        bool is_unit() const noexcept;

        Vector4D& operator +=(const Vector4D&) noexcept;
        Vector4D& operator -=(const Vector4D&) noexcept;
        Vector4D& operator *=(double) noexcept;
        Vector4D& operator /=(double) noexcept;

        bool is_perpendicular_on(const Vector4D& v) const noexcept
        {
            return dot(v) == approx(0.0);
        }
    };

    Vector4D operator +(const Vector4D&, const Vector4D&) noexcept;
    Vector4D operator -(const Vector4D&) noexcept;
    Vector4D operator -(const Vector4D&, const Vector4D&) noexcept;
    Vector4D operator *(const Vector4D&, double) noexcept;
    Vector4D operator *(double, const Vector4D&) noexcept;
    Vector4D operator /(const Vector4D&, double) noexcept;

    bool operator ==(const Vector4D&, const Vector4D&) noexcept;
    bool operator !=(const Vector4D&, const Vector4D&) noexcept;

    std::ostream& operator <<(std::ostream&, const Vector4D&);

    template<>
    struct approximately<Vector4D>
    {
        Vector4D value;
        double delta;

        explicit approximately(const Vector4D& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const Vector4D& other) const
        {
            return (value - other).norm() < delta;
        }
    };
}
