#pragma once

#include "imaging/color.h"
#include "math/ray.h"
#include "raytracing/scene.h"


namespace raytracer
{
    class RayTracer
    {
    public:
        virtual imaging::color trace(const Scene&, const math::Ray&) const = 0;
    };
}