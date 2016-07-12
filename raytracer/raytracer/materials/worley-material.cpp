#include "materials/worley-material.h"
#include "materials/brdf.h"
#include "materials/brdfs/lambert.h"
#include "math/functions/worley.h"

using namespace raytracer;
using namespace raytracer::materials;
using namespace math;
using namespace imaging;


raytracer::materials::_private_::WorleyMaterial3D::WorleyMaterial3D()
    : m_noise_function(math::functions::worley3d())
{
    // NOP
}

MaterialProperties raytracer::materials::_private_::WorleyMaterial3D::at(const HitPosition& hp) const
{
    Point3D p = hp.xyz;

    MaterialProperties properties;
    properties.ambient = colors::black();
    properties.diffuse = this->m_noise_function(p) * colors::white();
    properties.specular = colors::black();
    properties.specular_exponent = 0.0;
    properties.reflectivity = 0.0;

    return properties;
}

Material raytracer::materials::worley()
{
    return Material(std::make_shared<_private_::WorleyMaterial3D>());
}