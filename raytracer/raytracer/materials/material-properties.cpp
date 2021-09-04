#include "materials/material-properties.h"


raytracer::MaterialProperties::MaterialProperties(
    const imaging::Color& ambient,
    const imaging::Color& diffuse,
    const imaging::Color& specular,
    double specular_exponent,
    double reflectivity,
    double opacity,
    double transparency,
    double refractive_index)
    : ambient(ambient)
    , diffuse(diffuse)
    , specular(specular)
    , specular_exponent(specular_exponent)
    , reflectivity(reflectivity)
    , opacity(opacity)
    , transparency(transparency)
    , refractive_index(refractive_index)
{
    // NOP
}