#pragma once

#include "raytracing/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV0 : public RayTracerImplementation
            {
            public:
                TraceResult trace(const Scene&, const math::Ray&) const override;
            };
        }

        RayTracer v0();
    }
}