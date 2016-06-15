#define _USE_MATH_DEFINES
#include "Sphere.h"
#include "materials/material.h"
#include "materials/material2d.h"
#include "materials/material3d.h"
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

		auto material2d = std::dynamic_pointer_cast<Material2D>(hit->material);
		if (material2d != nullptr)
		{
			double u = 0.5 + atan2(hit->position.z, hit->position.x) / (2 * M_PI);
			double v = 0.5 - asin(hit->position.y) / M_PI;

			assert(0 <= u);
			assert(u <= 1);
			assert(0 <= v);
			assert(v <= 1);

			Point2D uv(u, v);

			hit->c = material2d->at(uv);
		}
		else
		{
			auto material3d = std::dynamic_pointer_cast<Material3D>(hit->material);

			assert(material3d != nullptr);

			hit->c = material3d->at(hit->position);
		}

		return true;
	}
	else
	{
		return false;
	}
}