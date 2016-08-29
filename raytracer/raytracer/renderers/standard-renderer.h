#pragma once

#include "renderers/renderer.h"
#include "renderers/renderer.h"
#include <functional>


namespace raytracer
{
    namespace renderers
    {
        Renderer standard(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<loopers::Looper>);
    }
}