#include "materials/worley-material.h"
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
    MaterialProperties properties(colors::black(), this->m_noise_function(p) * colors::white(), colors::black(), 0.0, 0.0, 0.0, 0.0);

    return properties;
}

Material raytracer::materials::worley()
{
    return Material(std::make_shared<_private_::WorleyMaterial3D>());
}