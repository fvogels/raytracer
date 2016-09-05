#pragma once

#include "primitives/primitive.h"
#include <iostream>


namespace raytracer
{
    namespace primitives
    {
        Primitive mesh(const std::vector<Primitive>&);
        Primitive mesh(std::vector<Primitive>&&);

        Primitive load_mesh(std::istream&);
    }
}