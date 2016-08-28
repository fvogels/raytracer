#pragma once

#include "primitives/primitive.h"
#include <iostream>


namespace raytracer
{
    namespace primitives
    {
        Primitive load_mesh(std::istream&);
    }
}