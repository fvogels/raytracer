#pragma once

#include "rendering/renderer.h"


namespace raytracer
{
    namespace rendering
    {
        Renderer cartoon(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>, unsigned, double);
    }
}