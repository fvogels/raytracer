#pragma once

#include "rendering/light-ray.h"
#include "math/point3d.h"
#include <vector>


namespace raytracer
{
    class LightSource
    {
    public:
        virtual std::vector<LightRay> lightrays_to(const math::Point3D&) const = 0;
    };
}