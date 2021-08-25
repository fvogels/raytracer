#pragma once

#include "primitives/primitive.h"
#include <vector>
#include <memory>


namespace raytracer
{
    namespace primitives
    {
        Primitive bounding_box_accelerator(Primitive);
        Primitive accelerated_union(std::vector<Primitive>&);
    }
}