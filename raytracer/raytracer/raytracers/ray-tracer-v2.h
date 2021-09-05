#pragma once

#include "raytracers/ray-tracer-v1.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV2 : public RayTracerV1
            {
            protected:
                imaging::Color determine_color(const Scene&, const MaterialProperties&, const Hit&, const math::Ray& eye_ray) const override;

                virtual imaging::Color process_lights(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&) const;
                virtual imaging::Color process_light_source(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, LightSource) const;
                virtual imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
                imaging::Color compute_diffuse(const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
            };
        }

        RayTracer v2();
    }
}