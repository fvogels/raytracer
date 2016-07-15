#pragma once

#include "materials/material.h"
#include "math/functions/noise.h"
#include "animation/time-stamp.h"


namespace raytracer
{
    namespace materials
    {
        Material marble2d(unsigned, double);
        Material marble3d(unsigned, double);
    }
}