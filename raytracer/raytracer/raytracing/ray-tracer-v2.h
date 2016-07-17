#pragma once

#include "raytracing/ray-tracer-v1.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV2 : public RayTracerV1
            {
            public:
                imaging::color trace(const Scene&, const math::Ray&) const override;

            protected:
                virtual imaging::color process_lights(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&) const;
                virtual imaging::color process_light_source(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, LightSource) const;
                virtual imaging::color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
                imaging::color compute_diffuse(const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
            };
        }

        RayTracer v2();
    }
}