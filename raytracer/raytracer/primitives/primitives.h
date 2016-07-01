#pragma once

#include "primitives/primitive.h"
#include "math/transformation.h"
#include "math/angle.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include "primitives/cropper.h"
#include "primitives/disk.h"
#include "primitives/union.h"
#include "primitives/decorator.h"
#include "primitives/cylinder.h"
#include "primitives/sphere.h"
#include "primitives/intersection.h"
#include "primitives/plane.h"
#include <memory>
#include <vector>


namespace raytracer
{
    namespace primitives
    {
        Primitive transform(const math::Transformation&, Primitive);
        Primitive translate(const math::Vector3D&, Primitive);
        Primitive scale(double, double, double, Primitive);
        Primitive rotate_around_x(math::Angle, Primitive);
        Primitive rotate_around_y(math::Angle, Primitive);
        Primitive rotate_around_z(math::Angle, Primitive);
    }
}