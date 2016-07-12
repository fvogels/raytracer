#pragma once

#include "primitives/primitives.h"
#include "lights/lights.h"
#include "cameras/camera.h"


namespace raytracer
{
    struct Scene
    {
        raytracer::Primitive root;
        std::vector<LightSource> light_sources;
        raytracer::Camera camera;
    };
}