#pragma once

#include "math/functions/noise.h"


namespace math
{
    namespace functions
    {
        Noise2D perlin2d(unsigned seed = 0);
        Noise2D marble2d(unsigned, double);
    }
}