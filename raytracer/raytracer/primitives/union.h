#pragma once

#include "primitives/primitive.h"
#include <vector>
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            
        }

        Primitive make_union(std::vector<Primitive>&);
    }
}