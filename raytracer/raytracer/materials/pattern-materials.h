#pragma once

#include "materials/material.h"
#include "materials/marble-material.h"
#include "materials/wood-material.h"
#include "materials/texture-material.h"
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
        Material polka(double, Material, Material);
        Material polka(double, double, Material, Material);
        Material dalmatian(unsigned, Material, Material);
    }
}