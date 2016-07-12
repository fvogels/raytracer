#pragma once

#include "imaging/color.h"


namespace raytracer
{
    struct MaterialProperties
    {
        imaging::color ambient;
        imaging::color diffuse;
        imaging::color specular;
        double specular_exponent;
        double reflectivity;
    };
}