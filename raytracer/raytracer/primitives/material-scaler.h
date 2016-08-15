#pragma once

#include "primitives/primitive.h"
#include "materials/material.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        Primitive scale_material2d(double sx, double sy, Primitive child);
    }
}