#pragma once

#include "math/functions/noise.h"


namespace math
{
    namespace functions
    {
        Noise1D perlin1d(unsigned, unsigned);
        Noise1D perlin1d(unsigned);
        Noise2D perlin2d(unsigned);
        Noise2D perlin2d(unsigned, unsigned);
        Noise3D perlin3d(unsigned);
        Noise3D perlin3d(unsigned, unsigned);
        Noise2D marble2d(unsigned, double);
        Noise3D marble3d(unsigned, double);
        Noise2D wood2d(unsigned, double);

        Function<Vector3D(const Point3D&)> perlin_vector3d(unsigned);
    }
}