#pragma once

#include "patterns/pattern.h"
#include "patterns/lambda-pattern.h"
#include "math/angle.h"


namespace patterns
{
    Pattern2D make_pattern(std::function<bool(double, math::Angle)> function);
}
