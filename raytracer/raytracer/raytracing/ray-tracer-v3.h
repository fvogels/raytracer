#pragma once

#include "raytracing/ray-tracer-v2.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV3 : public RayTracerV2
            {
            protected:
                imaging::color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const override;

                imaging::color compute_specular(const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
            };
        }

        RayTracer v3();
    }
}