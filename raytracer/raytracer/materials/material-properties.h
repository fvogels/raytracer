#pragma once

#include "imaging/color.h"


namespace raytracer
{
    struct MaterialProperties
    {
        MaterialProperties(const imaging::Color& ambient, const imaging::Color& diffuse, const imaging::Color& specular, double specular_exponent, double reflectivity, double transparency, double refractive_index);

        const imaging::Color ambient;
        const imaging::Color diffuse;
        const imaging::Color specular;
        const double specular_exponent;
        const double reflectivity;
        const double transparency;
        const double refractive_index;
    };
}