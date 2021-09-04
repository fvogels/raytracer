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
            };
        }

        RayTracer v6(double minimum_weight = 0.01);
    }
}