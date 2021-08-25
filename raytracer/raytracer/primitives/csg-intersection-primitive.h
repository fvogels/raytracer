#pragma once

#include "primitives/primitive.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        Primitive csg_intersection(Primitive, Primitive);
    }
}