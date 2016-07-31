#pragma once

#include "materials/material.h"
#include "imaging/bitmap.h"
#include "math/function.h"
#include "math/point2d.h"


namespace raytracer
{
    namespace materials
    {
        Material texture(math::Function<imaging::Color(const math::Point2D&)>);
        Material texture(std::shared_ptr<imaging::Bitmap>);
        Material texture(const std::string&);
    }
}