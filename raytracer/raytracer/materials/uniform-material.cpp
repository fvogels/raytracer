#include "materials/uniform-material.h"

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::materials::UniformMaterial::UniformMaterial(const color& diffuse, const color& specular, double specular_exponent, double reflectivity)
    : m_diffuse(diffuse), m_specular(specular), m_specular_exponent(specular_exponent), m_reflectivity(reflectivity) { }

MaterialProperties raytracer::materials::UniformMaterial::at(const HitPosition&) const
{
    MaterialProperties properties;

    properties.diffuse = m_diffuse;
    properties.specular = m_specular;
    properties.specular_exponent = m_specular_exponent;
    properties.reflectivity = m_reflectivity;

    return properties;
}