#include "materials/uniform-material.h"

using namespace math;

color raytracer::UniformMaterial::at(const Point3D&) const
{
	return this->c;
}