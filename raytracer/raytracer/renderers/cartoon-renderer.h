#pragma once

#include "renderers/renderer.h"


namespace raytracer
{
    namespace renderers
    {
        Renderer cartoon(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>, unsigned, double);
    }
}