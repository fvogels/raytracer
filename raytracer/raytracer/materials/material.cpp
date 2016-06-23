#include "materials/material.h"

using namespace math;
using namespace raytracer;


MaterialProperties raytracer::Material2D::at(const HitPosition& hp) const
{
	return at(hp.uv);
}

MaterialProperties raytracer::Material3D::at(const HitPosition& hp) const
{
	return at(hp.xyz);
}