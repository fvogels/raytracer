#pragma once

#include "patterns/pattern.h"
#include <functional>


namespace patterns
{
    namespace _private_
    {
        
    }

    Pattern2D make_pattern(std::function<bool(const math::Point2D&)> function);
    Pattern3D make_pattern(std::function<bool(const math::Point3D&)> function);
}
