#pragma once

#include "patterns/pattern.h"
#include "math/point.h"


namespace math
{
    namespace functions
    {
        Pattern2D dalmatian2d(unsigned density, unsigned seed);
        Pattern3D dalmatian3d(unsigned density, unsigned seed);
    }
}
