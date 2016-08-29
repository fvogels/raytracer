#pragma once

#include "math/functions/noise.h"


namespace math
{
    namespace functions
    {
        Noise2D worley2d(unsigned density = 1, unsigned seed = 0);
        Noise3D worley3d(unsigned seed = 0);
    }
}