#include "materials/UniformMaterial.h"

using namespace math;

color Raytracer::UniformMaterial::at(const Point3D&) const
{
	return this->c;
}