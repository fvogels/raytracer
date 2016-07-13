#include "materials/perlin-material.h"
#include "math/functions/perlin.h"

using namespace raytracer;
using namespace raytracer::materials;
using namespace math;
using namespace imaging;


raytracer::materials::_private_::PerlinMaterial2D::PerlinMaterial2D()
    : m_noise_function(math::functions::perlin2d())
{
    // NOP
}

MaterialProperties raytracer::materials::_private_::PerlinMaterial2D::at(const HitPosition& hp) const
{
    Point2D p = hp.uv;

    MaterialProperties properties;
    properties.ambient = colors::black();
    properties.diffuse = this->m_noise_function(p) * colors::white();
    properties.specular = colors::black();
    properties.specular_exponent = 0.0;
    properties.reflectivity = 0.0;

    return properties;
}

Material raytracer::materials::perlin2d()
{
    return Material(std::make_shared<_private_::PerlinMaterial2D>());
}