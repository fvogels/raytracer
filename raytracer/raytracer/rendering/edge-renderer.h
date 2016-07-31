#pragma once

#include "rendering/renderer.h"


namespace raytracer
{
    namespace rendering
    {
        Renderer edge(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>, double);
    }
}