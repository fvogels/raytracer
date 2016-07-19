#pragma once

#include "primitives/primitive.h"
#include <iostream>


namespace raytracer
{
    namespace primitives
    {
        Primitive fast_mesh(std::istream&);
        Primitive fast_mesh_bin(std::istream&);
    }
}