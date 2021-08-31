#pragma once

#include "math/functions/pattern.h"
#include "math/angle.h"
#include <functional>


namespace math
{
    namespace functions
    {
        namespace patterns
        {
            Pattern2D grid(double xthickness, double ythickness, double xspacing, double yspacing);
        }
    }
}