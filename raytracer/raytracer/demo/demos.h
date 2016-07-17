#pragma once

#include "raytracing/scene.h"
#include "math/function.h"
#include "animation/animation.h"
#include <memory>


namespace demos
{
    animation::Animation<std::shared_ptr<raytracer::Scene>> marble_animation();
}