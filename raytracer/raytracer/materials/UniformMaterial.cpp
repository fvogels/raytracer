#include "materials/UniformMaterial.h"

using namespace math;

color Raytracer::UniformMaterial::at(const point3d&) const
{
	return this->c;
}