#pragma once

#include "materials/material.h"


namespace raytracer
{
    namespace materials
    {
        Material perlin2d(unsigned seed, unsigned octaves, math::Function<MaterialProperties(double)>);
        Material perlin3d(unsigned seed, unsigned octaves, math::Function<MaterialProperties(double)>);
    }
}
