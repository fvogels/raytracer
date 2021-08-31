#pragma once

#include "materials/material.h"
#include "math/function.h"
#include "patterns/pattern.h"
#include "math/point.h"


namespace raytracer
{
    namespace materials
    {
        Material pattern2d(patterns::Pattern2D, Material, Material);
        Material pattern3d(patterns::Pattern3D, Material, Material);        
    }
}