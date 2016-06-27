#pragma once

#include "math/function.h"
#include "math/vector3d.h"


namespace raytracer
{
    class BRDF : public math::FunctionBody<double, const math::Vector3D&, const math::Vector3D&>
    {
        // EMPTY
    };
}