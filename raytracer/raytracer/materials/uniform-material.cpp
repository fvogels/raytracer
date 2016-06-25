#include "materials/uniform-material.h"

using namespace math;
using namespace raytracer;


MaterialProperties raytracer::materials::UniformMaterial::at(const HitPosition&) const
{
	MaterialProperties properties;

	properties.diffuse = this->m_diffuse;

	return properties;
}