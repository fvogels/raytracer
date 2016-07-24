#pragma once

#include "pipeline/processor.h"
#include "animation/animation.h"
#include "raytracing/scene.h"


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Processor<animation::Animation<std::shared_ptr<Scene>>, std::shared_ptr<Scene>>> animation(double);
    }
}