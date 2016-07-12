#pragma once

#include "raytracing/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class FastRayTracer : public RayTracerImplementation
            {
            public:
                FastRayTracer(double weight_bound);

                imaging::color trace(const Scene&, const math::Ray&) const override;

            private:
                imaging::color trace(const Scene&, const math::Ray&, double) const;

                double m_weight_bound;
            };
        }

        RayTracer fast_ray_tracer(double weight_bound = 0.01);
    }
}