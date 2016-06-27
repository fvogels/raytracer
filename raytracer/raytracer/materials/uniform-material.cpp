#include "materials/uniform-material.h"

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::materials::UniformMaterial::UniformMaterial(const MaterialProperties& properties)
    : m_properties(properties)
{
    // NOP
}

MaterialProperties raytracer::materials::UniformMaterial::at(const HitPosition&) const
{
    return m_properties;
}