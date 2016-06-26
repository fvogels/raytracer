#pragma once

#include "math/util.h"
#include <iostream>


namespace math
{
    struct Vector3D final
    {
        double x, y, z;

        Vector3D() noexcept
            : x(0), y(0), z(0) { }

        Vector3D(double x, double y, double z) noexcept
            : x(x), y(y), z(z) { }

        Vector3D(const Vector3D& v) noexcept = default;

        Vector3D& operator =(const Vector3D&) noexcept = default;

        double dot(const Vector3D&) const noexcept;
        Vector3D cross(const Vector3D&) const noexcept;

        double norm_sqr() const noexcept;
        double norm() const noexcept;
        void normalize() noexcept;
        Vector3D normalized() const noexcept;
        bool is_unit() const noexcept;

        Vector3D& operator +=(const Vector3D&) noexcept;
        Vector3D& operator -=(const Vector3D&) noexcept;
        Vector3D& operator *=(double) noexcept;
        Vector3D& operator /=(double) noexcept;

        bool is_perpendicular_on(const Vector3D& v) const noexcept
        {
            return dot(v) == approx<double>(0);
        }

        Vector3D reflect_by(const Vector3D&) const;
    };

    Vector3D operator +(const Vector3D&, const Vector3D&) noexcept;
    Vector3D operator -(const Vector3D&) noexcept;
    Vector3D operator -(const Vector3D&, const Vector3D&) noexcept;
    Vector3D operator *(const Vector3D&, double) noexcept;
    Vector3D operator *(double, const Vector3D&) noexcept;
    Vector3D operator /(const Vector3D&, double) noexcept;

    bool operator ==(const Vector3D&, const Vector3D&) noexcept;
    bool operator !=(const Vector3D&, const Vector3D&) noexcept;

    std::ostream& operator <<(std::ostream&, const Vector3D&);

    template<>
    struct approx<Vector3D>
    {
        Vector3D value;
        double delta;

        explicit approx(const Vector3D& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const Vector3D& other) const
        {
            return (value - other).norm() < delta;
        }
    };
}