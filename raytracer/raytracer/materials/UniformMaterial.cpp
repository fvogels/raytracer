#include "materials/UniformMaterial.h"

using namespace math;

color raytracer::UniformMaterial::at(const point3d&) const
{
	return this->c;
}