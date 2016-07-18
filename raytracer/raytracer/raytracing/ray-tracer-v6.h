#pragma once

#include "raytracing/ray-tracer-v5.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV6 : public RayTracerV5
            {
            public:
                using RayTracerV5::RayTracerV5;

                imaging::color trace(const Scene&, const math::Ray&) const override;

            protected:
                virtual imaging::color trace(const Scene&, const math::Ray&, double) const;

                imaging::color compute_refraction(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;
            };
        }

        RayTracer v6(double minimum_weight = 0.01);
    }
}