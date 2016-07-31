#pragma once

#include "primitives/primitive.h"
#include "math/transformation.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        Primitive bumpify(math::Function<math::Vector3D(const math::Point3D&)>, Primitive);
    }
}