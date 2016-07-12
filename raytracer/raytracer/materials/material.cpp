#include "materials/material.h"

using namespace math;
using namespace raytracer;


MaterialProperties raytracer::materials::_private_::Material2D::at(const HitPosition& hp) const
{
    return at(hp.uv);
}

MaterialProperties raytracer::materials::_private_::Material3D::at(const HitPosition& hp) const
{
    return at(hp.xyz);
}