#pragma once

#include "renderers/renderer.h"
#include "tasks/task-scheduler.h"


namespace raytracer
{
    namespace renderers
    {
        Renderer masking(Renderer image_renderer, Renderer mask_renderer);
    }
}