#pragma once

#include "primitives/primitive.h"
#include "math/transformation3d.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        Primitive group(unsigned, Primitive);
    }
}