#pragma once

#include "primitives/primitive.h"
#include <iostream>


namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {

        }

        Primitive load_mesh(std::istream&);
    }
}