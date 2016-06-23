#define _USE_MATH_DEFINES
#include "Cylinder.h"
#include "materials/material.h"
#include "materials/material2d.h"
#include "materials/material3d.h"
#include "util/misc.h"
#include <assert.h>
#include <math.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
	std::shared_ptr<Hit> create_hit(const Ray& ray, const Context& context, double t)
	{
		auto hit = std::make_shared<Hit>();

		hit->position = ray.at(hit->t);
		hit->normal = Vector3D(hit->position.x, hit->position.y, 0);

		auto material2d = std::dynamic_pointer_cast<Material2D>(context.material);
		if (material2d != nullptr)
		{
			double u = 0.5 + atan2(hit->position.y, hit->position.x) / (2 * M_PI);
			double v = hit->position.z;

			assert(0 <= u);
			assert(u <= 1);

			Point2D uv(u, v);

			hit->c = material2d->at(uv);
		}
		else
		{
			auto material3d = std::dynamic_pointer_cast<Material3D>(hit->material);

			assert(material3d != nullptr);

			hit->c = material3d->at(hit->position);
		}

		return hit;
	}
}

bool raytracer::primitives::Cylinder::find_hit(const Ray& ray, Hit* hit) const
{
	assert(hit != nullptr);

	Point2D O(ray.origin.x, ray.origin.y);
	Vector2D D(ray.direction.x, ray.direction.y);

	if ((O - Point2D()).norm_sqr() > 1)
	{
		double a = D.dot(D);
		double b = 2 * D.dot(O - Point2D());
		double c = (O - Point2D()).norm_sqr() - 1;
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

			hit->position = ray.at(hit->t);
			hit->normal = Vector3D(hit->position.x, hit->position.y, 0);

			auto material2d = std::dynamic_pointer_cast<Material2D>(hit->material);
			if (material2d != nullptr)
			{
				double u = 0.5 + atan2(hit->position.y, hit->position.x) / (2 * M_PI);
				double v = hit->position.z;

				assert(0 <= u);
				assert(u <= 1);

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
	else
	{
		return false;
	}
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::Cylinder::hits(const math::Ray& ray, const Context& context) const
{
	Point2D O(ray.origin.x, ray.origin.y);
	Vector2D D(ray.direction.x, ray.direction.y);

	if ((O - Point2D()).norm_sqr() > 1)
	{
		double a = D.dot(D);
		double b = 2 * D.dot(O - Point2D());
		double c = (O - Point2D()).norm_sqr() - 1;
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

			auto hits = std::vector<std::shared_ptr<Hit>>();

			hits.push_back(create_hit(ray, context, t1));
			hits.push_back(create_hit(ray, context, t2));

			return hits;
		}
		else
		{
			return std::vector<std::shared_ptr<Hit>>();
		}
	}
	else
	{
		return std::vector<std::shared_ptr<Hit>>();
	}
}