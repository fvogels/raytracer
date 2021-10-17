#pragma once

#include "renderers/renderer.h"
#include "imaging/color.h"

namespace raytracer
{
    namespace renderers
    {
        Renderer simple_edge(unsigned, unsigned, raytracer::Sampler, RayTracer, tasks::TaskScheduler scheduler, const imaging::Color&, const imaging::Color&);
    }
}