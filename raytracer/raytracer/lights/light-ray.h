#pragma once

#include "math/ray.h"
#include "imaging/color.h"


namespace raytracer
{
    struct LightRay
    {
        LightRay(const math::Ray&, const imaging::color&);

        math::Ray ray;
        imaging::color color;
    };
}