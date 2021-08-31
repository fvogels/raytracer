#pragma once

#include "math/functions/pattern.h"
#include "math/point.h"
#include "math/transformation2d.h"
#include "math/transformation3d.h"
#include <memory>


namespace math
{
    namespace functions
    {
        namespace patterns
        {
            Pattern2D conjunction(Pattern2D pattern1, Pattern2D pattern2);
            Pattern2D disjunction(Pattern2D pattern1, Pattern2D pattern2);
            Pattern2D exclusive_disjunction(Pattern2D pattern1, Pattern2D pattern2);
            Pattern2D negation(Pattern2D pattern);

            Pattern3D conjunction(Pattern3D pattern1, Pattern3D pattern2);
            Pattern3D disjunction(Pattern3D pattern1, Pattern3D pattern2);
            Pattern3D exclusive_disjunction(Pattern3D pattern1, Pattern3D pattern2);
            Pattern3D negation(Pattern3D pattern);
        }
    }
}