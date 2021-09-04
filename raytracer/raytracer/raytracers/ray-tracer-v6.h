#pragma once

#include "raytracers/ray-tracer-v5.h"
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

            protected:
                virtual TraceResult trace(const Scene&, const math::Ray&, double) const;
                
                imaging::Color compute_own_color(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;
                imaging::Color compute_see_through_color(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;
            };
        }

        RayTracer v6(double minimum_weight = 0.01);
    }
}