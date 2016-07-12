#pragma once

#include "raytracing/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class FastRayTracer : public RayTracer
            {
            public:
                FastRayTracer(double weight_bound);

                imaging::color trace(const Scene&, const math::Ray&) const override;

            private:
                imaging::color trace(const Scene&, const math::Ray&, double) const;

                double m_weight_bound;
            };
        }

        std::shared_ptr<RayTracer> fast_ray_tracer(double weight_bound = 0.01);
    }
}