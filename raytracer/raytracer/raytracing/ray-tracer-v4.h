#pragma once

#include "raytracing/ray-tracer-v3.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV4 : public RayTracerV3
            {
            protected:
                imaging::color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const override;
            };
        }

        RayTracer v4();
    }
}