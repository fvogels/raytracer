#pragma once

#include "raytracing/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV1 : public RayTracerImplementation
            {
            public:
                imaging::color trace(const Scene&, const math::Ray&) const override;

            protected:
                imaging::color compute_ambient(const MaterialProperties&) const;
            };
        }

        RayTracer v1();
    }
}