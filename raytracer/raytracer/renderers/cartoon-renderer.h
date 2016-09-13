#pragma once

#include "renderers/renderer.h"
#include "tasks/task-scheduler.h"


namespace raytracer
{
    namespace renderers
    {
        Renderer cartoon(unsigned, unsigned, raytracer::Sampler, RayTracer, tasks::TaskScheduler, unsigned, double);
    }
}