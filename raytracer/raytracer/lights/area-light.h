#pragma once

#include "lights/point-light.h"
#include "math/rectangle3d.h"
#include "samplers/sampler.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        LightSource area(const math::Rectangle3D&, raytracer::Sampler, const imaging::Color&);
    }
}