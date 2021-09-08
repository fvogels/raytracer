#pragma once

#include "patterns/pattern.h"
#include "math/angle.h"
#include <functional>


namespace patterns
{
    Pattern2D revolution(std::function<double(math::Angle)> function);
}
