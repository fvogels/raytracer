#pragma once

#include "materials/material.h"
#include "math/function.h"
#include "math/point.h"

namespace raytracer
{
    namespace materials
    {
        Material pattern2d(math::Function<bool(const math::Point2D&)>, Material, Material);
        Material pattern3d(math::Function<bool(const math::Point3D&)>, Material, Material);
        Material horizontal_lines(double, Material, Material);
        Material vertical_lines(double, Material, Material);
        Material grid2d(double, Material, Material);
        Material grid3d(double, Material, Material);
        Material checkered2d(Material, Material);
        Material checkered3d(Material, Material);
        Material polka(double radius, Material, Material);
        Material polka(double radius1, double radius2, Material, Material);
        Material dalmatian2d(unsigned density, Material, Material);
        Material dalmatian3d(unsigned density, Material, Material);
    }
}