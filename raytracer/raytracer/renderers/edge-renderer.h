#pragma once

#include "renderers/renderer.h"


namespace raytracer
{
    namespace renderers
    {
        Renderer edge(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<loopers::Looper>, double);
    }
}