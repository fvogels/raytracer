#pragma once

#include "math/function.h"
#include "math/vector3d.h"
#include "imaging/color.h"


namespace raytracer
{
    class BRDFBody : public math::FunctionBody<imaging::Color, const math::Vector3D&, const imaging::Color&, const math::Vector3D&, const math::Vector3D&>
    {
        // EMPTY
    };

    typedef math::Function<imaging::Color(const math::Vector3D&, const imaging::Color&, const math::Vector3D&, const math::Vector3D&)> BRDF;
}