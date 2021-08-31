#include "materials/material.h"
#include "materials/composition-material.h"
#include "materials/pattern-materials.h"
#include "math/function.h"
#include "math/functions.h"
#include "math/functions/noise.h"
#include "math/functions/bool-mapper.h"
#include "imaging/color-mapper.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::materials;
using namespace imaging;


Material raytracer::materials::pattern2d(math::functions::Pattern2D pattern, Material m1, Material m2)
{
    std::function<Material(const Point2D& point)> function = [=](const Point2D& point) -> Material {
        return pattern(point) ? m1 : m2;
    };

    return composite(from_lambda(function));
}

Material raytracer::materials::pattern3d(math::functions::Pattern3D pattern, Material m1, Material m2)
{
    std::function<Material(const Point3D& point)> function = [=](const Point3D& point) -> Material {
        return pattern(point) ? m1 : m2;
    };

    return composite(from_lambda(function));
}
