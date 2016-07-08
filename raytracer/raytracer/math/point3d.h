#pragma once

#include "math/vector3d.h"

namespace math
{
    struct Point3D final
    {
        double x, y, z;

        Point3D() noexcept
            : x(0), y(0), z(0) { }

        Point3D(double x, double y, double z) noexcept
            : x(x), y(y), z(z) { }

        Point3D(double r, math::Angle azimuth, math::Angle altitude)
            : x(r * cos(azimuth) * cos(altitude)), y(r * sin(altitude)), z(r * sin(azimuth) * cos(altitude)) { }

        Point3D(const Point3D& v) noexcept = default;

        static Point3D origin() noexcept
        {
            return Point3D(0, 0, 0);
        }

        static Point3D in_xz_plane(double r, math::Angle angle, double y = 0)
        {
            return Point3D(r * cos(angle), y, r * sin(angle));
        }

        static Point3D in_xy_plane(double r, math::Angle angle, double z = 0)
        {
            return Point3D(r * cos(angle), r * sin(angle), z);
        }

        static Point3D in_zy_plane(double r, math::Angle angle, double x = 0)
        {
            return Point3D(x, r * sin(angle), r * cos(angle));
        }

        Point3D& operator =(const Point3D&) noexcept = default;
    };

    Point3D operator +(const Point3D&, const Vector3D&) noexcept;
    Point3D operator +(const Vector3D&, const Point3D&) noexcept;
    Vector3D operator -(const Point3D&, const Point3D&) noexcept;
    Point3D operator -(const Point3D&, const Vector3D&) noexcept;

    bool operator ==(const Point3D&, const Point3D&) noexcept;
    bool operator !=(const Point3D&, const Point3D&) noexcept;

    double distance(const Point3D&, const Point3D&) noexcept;

    std::ostream& operator <<(std::ostream& out, const Point3D&);

    template<>
    struct approximately<Point3D>
    {
        Point3D value;
        double delta;

        explicit approximately(const Point3D& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const Point3D& other) const
        {
            return (value - other).norm() < delta;
        }
    };
}
