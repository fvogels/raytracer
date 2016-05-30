#include "primitives/Plane.h"
#include "math/util.h"
#include <assert.h>

using namespace Raytracer;
using namespace math;

Raytracer::Plane::Plane(const Point3D& point, const Vector3D& normal)
	: point(point), normal(normal)
{
	assert(normal.is_unit());
}

bool Raytracer::Plane::find_hit(const Ray& ray, Hit* hit) const
{
	double denominator = ray.direction.dot(this->normal);

	if (denominator != approx(0))
	{
		double numerator = (ray.origin - this->point).dot(this->normal);
		double t = numerator / denominator;

		if (0 <= t && t < hit->t)
		{
			hit->t = t;
			hit->normal = this->normal;
			hit->position = ray.at(t);

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}