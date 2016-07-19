#pragma once

#include "math/functions/noise.h"


namespace math
{
    namespace functions
    {
        Noise2D perlin2d(unsigned seed = 0);
        Noise3D perlin3d(unsigned seed = 0);
        Noise2D marble2d(unsigned, double);
        Noise3D marble3d(unsigned, double);
        Noise2D wood2d(unsigned, double);
    }
}