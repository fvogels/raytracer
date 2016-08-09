#pragma once

#include "math/functions/noise.h"


namespace math
{
    namespace functions
    {
        Noise1D perlin1d(unsigned, unsigned = 1);
        Noise2D perlin2d(unsigned, unsigned = 1);
        Noise3D perlin3d(unsigned, unsigned = 1);

        Function<Vector3D(const Point3D&)> perlin_vector3d(unsigned, unsigned = 1);

        template<typename R, typename T>
        math::Function<R(const T&)> perlin(unsigned, unsigned);

        template<>
        inline math::Function<double(const double&)> perlin<double, double>(unsigned octaves, unsigned seed)
        {
            return perlin1d(octaves, seed);
        }

        template<>
        inline math::Function<double(const Point2D&)> perlin<double, Point2D>(unsigned octaves, unsigned seed)
        {
            return perlin2d(octaves, seed);
        }

        template<>
        inline math::Function<double(const Point3D&)> perlin<double, Point3D>(unsigned octaves, unsigned seed)
        {
            return perlin3d(octaves, seed);
        }

        template<>
        inline math::Function<Vector3D(const Point3D&)> perlin<Vector3D, Point3D>(unsigned octaves, unsigned seed)
        {
            return perlin_vector3d(seed, octaves);
        }
    }
}