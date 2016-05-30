#include "materials/CheckeredMaterial.h"

using namespace math;

color Raytracer::CheckeredMaterial::at(const Point3D& p) const
{
	double sum = floor(p.x) + floor(p.y) + floor(p.z);

	return int(sum) % 2 == 0 ? c1 : c2;
}