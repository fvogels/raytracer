#pragma once

#include "math/function.h"
#include "math/vector3d.h"


namespace raytracer
{
    class BRDFBody : public math::FunctionBody<double, const math::Vector3D&, const math::Vector3D&, const math::Vector3D&>
    {
        // EMPTY
    };

    typedef math::Function<double, const math::Vector3D&, const math::Vector3D&, const math::Vector3D&> BRDF;
}