#pragma once

#include "raytracing/ray-tracer-v3.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV4 : public RayTracerV3
            {
            public:
                imaging::color trace(const Scene&, const math::Ray&) const override;
            };
        }

        RayTracer v4();
    }
}