#pragma once

#include "materials/material.h"
#include "math/function.h"
#include "math/point.h"

namespace raytracer
{
    namespace materials
    {
        Material pattern2d(math::Function<bool(const math::Point2D&)>, Material, Material);
        Material horizontal_lines(double, Material, Material);
        Material vertical_lines(double, Material, Material);
        Material grid(double, Material, Material);
        Material checkered(Material, Material);
        Material polka(double radius, Material, Material);
        Material polka(double radius1, double radius2, Material, Material);
        Material dalmatian2d(unsigned density, Material, Material);
    }
}