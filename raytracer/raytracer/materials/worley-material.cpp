#include "materials/worley-material.h"
#include "materials/brdf.h"
#include "materials/brdfs/lambert.h"
#include "math/functions/worley.h"

using namespace raytracer;
using namespace raytracer::materials;
using namespace math;


raytracer::materials::_private_::WorleyMaterial3D::WorleyMaterial3D()
    : m_noise_function(math::functions::worley3d())
{
    // NOP
}

MaterialProperties raytracer::materials::_private_::WorleyMaterial3D::at(const HitPosition& hp) const
{
    MaterialProperties properties;

    Point3D p = hp.xyz;
    properties.brdf = raytracer::brdfs::lambert(imaging::colors::white() * m_noise_function(Point3D(p.x * 5, p.y * 5, p.z * 5)));
    properties.reflective = false;

    return properties;
}

Material raytracer::materials::worley()
{
    return Material(std::make_shared<_private_::WorleyMaterial3D>());
}