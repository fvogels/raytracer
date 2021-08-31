#pragma once

#include "materials/material.h"
#include "math/function.h"
#include "patterns/pattern.h"
#include "math/point.h"

namespace raytracer
{
    namespace materials
    {
        Material pattern2d(math::functions::Pattern2D, Material, Material);
        Material pattern3d(math::functions::Pattern3D, Material, Material);        
    }
}