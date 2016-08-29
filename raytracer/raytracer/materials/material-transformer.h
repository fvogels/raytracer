#pragma once

#include "materials/material.h"
#include "math/transformation2d.h"
#include "math/transformation3d.h"


namespace raytracer
{
    namespace materials
    {
        Material transform(const math::Transformation2D& transformation, Material material);
        Material transform(const math::Transformation3D& transformation, Material material);

        Material scale(double x, double y, Material material);
        Material translate(const math::Vector2D& v, Material material);
        Material rotate(math::Angle angle, Material material);

        Material scale(double x, double y, double z, Material material);
        Material translate(const math::Vector3D& v, Material material);
        Material rotate_around_x(math::Angle angle, Material material);
        Material rotate_around_y(math::Angle angle, Material material);
        Material rotate_around_z(math::Angle angle, Material material);
    }
}