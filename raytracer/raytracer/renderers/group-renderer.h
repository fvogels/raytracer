#pragma once

#include "renderers/renderer.h"
#include "imaging/color.h"

namespace raytracer
{
    namespace renderers
    {
        Renderer group(unsigned, unsigned, raytracer::Sampler, RayTracer, tasks::TaskScheduler scheduler, const imaging::Color& background_color);
    }
}