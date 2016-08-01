#pragma once

#include "math/angle.h"
#include "math/interval.h"
#include <cmath>
#include <assert.h>


namespace math
{
    struct Cartesian2D
    {
        double x, y;
    };

    struct Polar
    {
        double radius;
        math::Angle theta;
    };

    struct Cartesian3D
    {
        double x, y, z;
    };

    struct Spherical
    {
        double radius;
        math::Angle azimuth, elevation;
    };

    namespace _private_
    {
        template<typename, typename>
        struct CoordinateConverter;

        template<>
        struct CoordinateConverter<Cartesian2D, Polar>
        {
            static Polar convert(const Cartesian2D& cartesian)
            {
                double radius = sqrt(pow(cartesian.x, 2) + pow(cartesian.y, 2));
                Angle theta = Angle::radians(atan2(cartesian.y, cartesian.x));

                return Polar{ radius, theta };
            }
        };

        template<>
        struct CoordinateConverter<Polar, Cartesian2D>
        {
            static Cartesian2D convert(const Polar& polar)
            {
                double x = polar.radius * cos(polar.theta);
                double y = polar.radius * sin(polar.theta);

                return Cartesian2D{ x, y };
            }
        };

        template<>
        struct CoordinateConverter<Cartesian3D, Spherical>
        {
            static Spherical convert(const Cartesian3D& cartesian)
            {
                double radius = sqrt(pow(cartesian.x, 2) + pow(cartesian.y, 2) + pow(cartesian.z, 2));
                Angle azimuth = Angle::radians(atan2(cartesian.z, cartesian.x));
                Angle elevation = radius > 0 ? 90_degrees - Angle::radians(acos(cartesian.y / radius)) : 0_degrees;

                assert(radius >= 0);
                assert(Interval<Angle>(-180_degrees, 180_degrees).contains(azimuth));
                assert(Interval<Angle>(-90_degrees, 90_degrees).contains(elevation));

                return Spherical{ radius, azimuth, elevation };
            }
        };

        template<>
        struct CoordinateConverter<Spherical, Cartesian3D>
        {
            static Cartesian3D convert(const Spherical& spherical)
            {
                double x = spherical.radius * cos(spherical.azimuth) * cos(spherical.elevation);
                double y = spherical.radius * sin(spherical.elevation);
                double z = spherical.radius * sin(spherical.azimuth) * cos(spherical.elevation);

                return Cartesian3D{ x,y,z };
            }
        };
    }

    template<typename TO, typename FROM>
    TO convert_coordinates(const FROM& from)
    {
        return _private_::CoordinateConverter<FROM, TO>::convert(from);
    }
}