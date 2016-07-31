#pragma once

#include "rendering/renderer.h"


namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            
        }

        Renderer split_depth(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>);
    }
}