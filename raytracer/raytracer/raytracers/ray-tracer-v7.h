#pragma once

#include "raytracers/ray-tracer-v6.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV7 : public RayTracerV6
            {
            public:
                using RayTracerV6::RayTracerV6;

            protected:
                virtual TraceResult trace(const Scene&, const math::Ray&, double) const;

                imaging::Color compute_own_color(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;
                imaging::Color compute_see_through_color(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;
            };
        }

        RayTracer v7(double minimum_weight = 0.01);
    }
}
