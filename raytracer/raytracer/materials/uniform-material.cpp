#include "materials/uniform-material.h"

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::materials::UniformMaterial::UniformMaterial(const color& diffuse, const color& specular, double specular_exponent)
    : m_diffuse(diffuse), m_specular(specular) { }

MaterialProperties raytracer::materials::UniformMaterial::at(const HitPosition&) const
{
    MaterialProperties properties;

    properties.diffuse = this->m_diffuse;
    properties.specular = this->m_specular;
    properties.specular_exponent = this->m_specular_exponent;

    return properties;
}