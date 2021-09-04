#pragma once

#include "raytracers/ray-tracer-v4.h"
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
                using RayTracerV4::RayTracerV4;

            protected:
                imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const override;
            };
        }

        RayTracer v5();
    }
}