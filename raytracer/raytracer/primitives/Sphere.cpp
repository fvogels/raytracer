#include "Sphere.h"
#include "util/misc.h"
#include <assert.h>
#include <math.h>

using namespace raytracer;
using namespace math;

bool Sphere::find_hit(const ray& ray, Hit* hit) const
{
	assert(hit != nullptr);

	double a = ray.direction.dot(ray.direction);
	double b = 2 * ray.direction.dot(ray.origin - point3d());
	double c = (ray.origin - point3d()).norm_sqr() - 1;
	double d = b * b - 4 * a * c;

	if (d >= 0)
	{
		double sqrt_d = std::sqrt(d);

		double t1 = (-b - sqrt_d) / (2 * a);
		double t2 = (-b + sqrt_d) / (2 * a);

		if (t1 > t2)
		{
			swap(t1, t2);
		}

		if (t1 > 0)
		{
			hit->t = t1;
			return true;
		}
		else if (t2 > 0)
		{
			hit->t = t2;
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