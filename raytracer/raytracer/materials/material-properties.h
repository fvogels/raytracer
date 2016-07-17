#pragma once

#include "imaging/color.h"


namespace raytracer
{
    struct MaterialProperties
    {
        MaterialProperties(const imaging::color&, const imaging::color&, const imaging::color&, double, double, double, double);

        const imaging::color ambient;
        const imaging::color diffuse;
        const imaging::color specular;
        const double specular_exponent;
        const double reflectivity;
        const double transparency;
        const double refractive_index;
    };
}