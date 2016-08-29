#pragma once

#include "materials/material.h"
#include "math/functions/noise.h"


namespace raytracer
{
    namespace materials
    {
        Material worley2d(unsigned density, double power);
        Material worley3d(unsigned density, double power);
    }
}