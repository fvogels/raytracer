#pragma once

#include "primitives/primitive.h"
#include <iostream>


namespace raytracer
{
    namespace primitives
    {
        Primitive fast_mesh(std::istream&);
    }
}