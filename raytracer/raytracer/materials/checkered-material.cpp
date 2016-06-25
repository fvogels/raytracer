#include "materials/checkered-material.h"
#include "easylogging++.h"

using namespace math;
using namespace raytracer;
using namespace imaging;


MaterialProperties raytracer::CheckeredMaterial3D::at(const Point3D& p) const
{
	double sum = floor(p.x) + floor(p.y) + floor(p.z);

	color c = int(sum) % 2 == 0 ? c1 : c2;

	MaterialProperties properties;
	properties.diffuse = c;

	return properties;
}