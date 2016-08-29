#pragma once

#include "materials/material.h"
#include "math/transformation2d.h"
#include "math/transformation3d.h"


namespace raytracer
{
    namespace materials
    {
        Material transform(const math::Transformation2D& transformation, Material material);
        Material transform(const math::Transformation3D& transformation, Material material);

        
    }
}