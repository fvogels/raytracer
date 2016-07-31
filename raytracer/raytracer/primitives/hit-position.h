#pragma once

#include "math/point.h"
#include "math/point.h"


namespace raytracer
{
    struct HitPosition
    {
        math::Point2D uv;
        math::Point3D xyz;
    };
}