#include "materials/uniform-material.h"

using namespace math;
using namespace raytracer;


MaterialProperties raytracer::UniformMaterial::at(const Point3D&) const
{
	MaterialProperties properties;

	properties.c = this->c;

	return properties;
}