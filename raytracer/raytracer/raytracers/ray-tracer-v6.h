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
                RayTracerV6(double);

                TraceResult trace(const Scene&, const math::Ray&) const override;

            protected:
                virtual TraceResult trace(const Scene&, const math::Ray&, double) const;

                virtual imaging::Color determine_color(const Scene&, const MaterialProperties&, const Hit&, const math::Ray& eye_ray, double weight) const;

                imaging::Color compute_reflection(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;

                double m_minimum_weight;
            };
        }

        RayTracer v6(double minimum_weight = 0.01);
    }
}