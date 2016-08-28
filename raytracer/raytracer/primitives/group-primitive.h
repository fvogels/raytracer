#pragma once

#include "primitives/primitive.h"
#include "math/transformation.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        Primitive group(unsigned, Primitive);
    }
}