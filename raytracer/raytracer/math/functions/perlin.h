#pragma once

#include "math/functions/noise.h"


namespace math
{
    namespace functions
    {
        Noise1D perlin1d(unsigned, unsigned = 1);
        Noise2D perlin2d(unsigned, unsigned = 1);
        Noise3D perlin3d(unsigned, unsigned = 1);

        Function<Vector3D(const Point3D&)> perlin_vector3d(unsigned);
    }
}