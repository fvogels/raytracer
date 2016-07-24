#pragma once

#include "raytracing/ray-tracer-v4.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV5 : public RayTracerV4
            {
            public:
                RayTracerV5(double);

                TraceResult trace(const Scene&, const math::Ray&) const override;

            protected:
                virtual TraceResult trace(const Scene&, const math::Ray&, double) const;
                imaging::Color compute_reflection(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;

                double m_minimum_weight;
            };
        }

        RayTracer v5(double minimum_weight = 0.01);
    }
}