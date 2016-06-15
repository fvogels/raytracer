#include "Sphere.h"
#include "util/misc.h"
#include <assert.h>
#include <math.h>

using namespace raytracer;
using namespace math;

bool Sphere::find_hit(const Ray& Ray, Hit* hit) const
{
	assert(hit != nullptr);

	double a = Ray.direction.dot(Ray.direction);
	double b = 2 * Ray.direction.dot(Ray.origin - Point3D());
	double c = (Ray.origin - Point3D()).norm_sqr() - 1;
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
		}
		else if (t2 > 0)
		{
			hit->t = t2;
		}
		else
		{
			return false;
		}

		hit->position = Ray.at(hit->t);
		hit->normal = hit->position - Point3D();
		hit->c = hit->material->at(hit->position);

		return true;
	}
	else
	{
		return false;
	}
}