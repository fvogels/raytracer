#pragma once

#include "renderers/renderer.h"
#include "loopers/looper.h"


namespace raytracer
{
    namespace renderers
    {
        Renderer cartoon(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<loopers::Looper>, unsigned, double);
    }
}