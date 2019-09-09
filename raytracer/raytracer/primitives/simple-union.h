#pragma once

#include "primitives/primitive.h"


namespace raytracer
{
    namespace primitives
    {
        Primitive simple_union(const std::vector<Primitive>&);
    }
}