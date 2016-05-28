#include "primitives/Plane.h"
#include "math/util.h"

using namespace raytracer;
using namespace math;

bool raytracer::Plane::find_hit(const ray& r, Hit* hit) const
{
	double denominator = r.direction.dot(this->normal);

	if (denominator != approx(0))
	{
		double numerator = (r.origin - this->point).dot(this->normal);
		double t = numerator / denominator;

		if (0 <= t && t < hit->t)
		{
			hit->t = t;
			hit->normal = this->normal;
			hit->position = r.at(t);

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