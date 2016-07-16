#pragma once

#include "raytracing/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class BinaryRayTracer : public RayTracerImplementation
            {
            public:
                imaging::color trace(const Scene&, const math::Ray&) const override;
            };
        }

        RayTracer binary();
    }
}