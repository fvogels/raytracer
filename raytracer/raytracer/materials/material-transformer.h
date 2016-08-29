#pragma once

#include "materials/material.h"
#include "math/transformation.h"


namespace raytracer
{
    namespace materials
    {
        Material transform2d(Material material, const math::Transformation& transformation);
    }
}