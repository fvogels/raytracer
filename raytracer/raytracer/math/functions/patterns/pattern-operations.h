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
            Pattern2D transform(const math::Transformation2D& transformation, Pattern2D pattern);

            Pattern2D translate(math::Vector2D displacement, Pattern2D pattern);
            Pattern2D rotate(math::Angle angle, Pattern2D pattern);
            Pattern2D scale(double sx, double sy, Pattern2D pattern);

            Pattern2D conjunction(Pattern2D pattern1, Pattern2D pattern2);
            Pattern2D disjunction(Pattern2D pattern1, Pattern2D pattern2);
            Pattern2D negation(Pattern2D pattern);

            Pattern2D tessellate(Pattern2D pattern, double width, double height);
        }
    }
}