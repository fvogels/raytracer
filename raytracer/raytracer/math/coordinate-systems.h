#pragma once

#include "math/angle.h"
#include <cmath>


namespace math
{
    struct Cartesian3D
    {
        double x, y, z;
    };

    struct SphericalRAZ
    {
        double radius, azimuth, zenith;
    };

    struct SphericalRAE
    {
        double radius;
        math::Angle azimuth, elevation;
    };

    namespace _private_
    {
        template<typename, typename>
        struct CoordinateConverter;

        template<>
        struct CoordinateConverter<Cartesian3D, SphericalRAE>
        {
            static SphericalRAE convert(const Cartesian3D& cartesian)
            {
                double radius = sqrt(pow(cartesian.x, 2) + pow(cartesian.y, 2) + pow(cartesian.z, 2));
                Angle azimuth = Angle::radians(atan2(cartesian.z, cartesian.x));
                Angle elevation = 90_degrees - Angle::radians(acos(cartesian.y / radius));

                return SphericalRAE{ radius, azimuth, elevation };
            }
        };
    }

    template<typename TO, typename FROM>
    TO convert_coordinates(const FROM& from)
    {
        return _private_::CoordinateConverter<FROM, TO>::convert(from);
    }
}