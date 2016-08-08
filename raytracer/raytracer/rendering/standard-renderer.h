#pragma once

#include "rendering/renderer.h"
#include "rendering/renderer.h"
#include <functional>


namespace raytracer
{
    namespace renderers
    {
        Renderer standard(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>);
    }
}