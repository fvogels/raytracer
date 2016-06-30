#pragma once

#include "primitives/primitives.h"
#include "lights/lights.h"


namespace raytracer
{
    struct Scene
    {
        raytracer::primitives::Primitive root;
        std::vector<std::shared_ptr<lights::LightSource>> light_sources;
    };
}