#pragma once

#include "primitives/primitives.h"
#include "lights/lights.h"
#include "cameras/camera.h"


namespace raytracer
{
    struct Scene
    {
        raytracer::primitives::Primitive root;
        std::vector<lights::LightSource> light_sources;
        raytracer::cameras::Camera camera;
    };
}