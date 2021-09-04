#pragma once

#include "raytracers/ray-tracer-v7.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV8 : public RayTracerV7
            {
            public:
                using RayTracerV7::RayTracerV7;

            protected:
                TraceResult trace(const Scene&, const math::Ray&, double) const override;

                imaging::Color compute_refraction(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;
            };
        }

        RayTracer v8(double minimum_weight = 0.01);
    }
}