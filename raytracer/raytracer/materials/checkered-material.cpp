#include "materials/checkered-material.h"
#include "easylogging++.h"

using namespace math;


color raytracer::CheckeredMaterial3D::at(const Point3D& p) const
{
	double sum = floor(p.x) + floor(p.y) + floor(p.z);

	return int(sum) % 2 == 0 ? c1 : c2;
}