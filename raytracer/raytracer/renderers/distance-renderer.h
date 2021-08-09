#pragma once

#include "renderers/renderer.h"
#include "math/point.h"
#include "imaging/color.h"

namespace raytracer
{
    namespace renderers
    {
        Renderer distance(unsigned, unsigned, raytracer::Sampler, RayTracer, tasks::TaskScheduler scheduler, const math::Point3D&, double, double);
    }
}
