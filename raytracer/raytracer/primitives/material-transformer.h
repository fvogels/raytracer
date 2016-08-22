#pragma once

#include "primitives/primitive.h"
#include "materials/material.h"
#include "math/matrix.h"
#include "math/angle.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        Primitive transform_material2d(const math::Matrix3D&, Primitive child);
        Primitive transform_material3d(const math::Matrix4D&, Primitive child);
        Primitive translate_material2d(const math::Vector2D& translation_vector, Primitive child);
        Primitive translate_material3d(const math::Vector3D& translation_vector, Primitive child);
        Primitive scale_material2d(double sx, double sy, Primitive child);
        Primitive scale_material3d(double sx, double sy, double sz, Primitive child);
        Primitive rotate_material(math::Angle angle, Primitive child);
        Primitive rotate_material_around_x(math::Angle angle, Primitive child);
        Primitive rotate_material_around_y(math::Angle angle, Primitive child);
        Primitive rotate_material_around_z(math::Angle angle, Primitive child);
    }
}