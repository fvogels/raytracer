#pragma once

#include "renderers/renderer.h"
#include "imaging/color.h"

namespace raytracer
{
    namespace renderers
    {
        Renderer edge(unsigned, unsigned, raytracer::Sampler, RayTracer, tasks::TaskScheduler scheduler, double, const imaging::Color&, const imaging::Color&);
    }
}