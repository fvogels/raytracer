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
                imaging::Color determine_color(const Scene&, const MaterialProperties&, const Hit&, const math::Ray& eye_ray, double weight) const override;
                imaging::Color compute_see_through_color(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;
            };
        }

        RayTracer v7(double minimum_weight = 0.01);
    }
}
