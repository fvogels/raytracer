#pragma once

#include "primitives/primitive.h"
#include "materials/material.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        Primitive decorate(Material, Primitive);
    }
}