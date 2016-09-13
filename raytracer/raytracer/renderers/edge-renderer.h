#pragma once

#include "renderers/renderer.h"


namespace raytracer
{
    namespace renderers
    {
        Renderer edge(unsigned, unsigned, raytracer::Sampler, RayTracer, tasks::TaskScheduler scheduler, double);
    }
}