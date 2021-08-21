#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
    namespace primitives
    {
        Primitive xy_square(double size);
        Primitive xz_square(double size);
        Primitive yz_square(double size);
    }
}