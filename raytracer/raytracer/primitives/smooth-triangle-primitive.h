#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
    namespace primitives
    {
        Primitive smooth_triangle(const math::Point3D&, const math::Point3D&, const math::Point3D&, const math::Vector3D&, const math::Vector3D&, const math::Vector3D&);
    }
}