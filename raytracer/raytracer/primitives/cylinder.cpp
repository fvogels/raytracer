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
	Point2D compute_uv_from_xyz(const Point3D& p)
	{
		double u = 0.5 + atan2(p.y, p.x) / (2 * M_PI);
		double v = p.z;

		assert(0 <= u);
		assert(u <= 1);

		return Point2D(u, v);
	}

	void initialize_hit(Hit* hit, const Ray& ray, double t)
	{
		hit->t = t;
		hit->position = ray.at(hit->t);
		hit->local_position.xyz = hit->position;
		hit->local_position.uv = compute_uv_from_xyz(hit->position);
		hit->normal = Vector3D(hit->position.x, hit->position.y, 0);
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

			// Compute both t's at which ray intersects cylinder
			double t1 = (-b - sqrt_d) / (2 * a);
			double t2 = (-b + sqrt_d) / (2 * a);

			// Find smallest t > 0
			double t;

			if (t1 > t2)
			{
				swap(t1, t2);
			}

			if (t1 > 0)
			{
				t = t1;
			}
			else if (t2 > 0)
			{
				t = t2;
			}
			else
			{
				// Both hits are behind the eye
				return false;
			}

			// Check if there's no better preexisting hit
			if (t < hit->t)
			{
				initialize_hit(hit, ray, t);

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
	else
	{
		return false;
	}
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::Cylinder::hits(const math::Ray& ray) const
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

			auto hit1 = std::make_shared<Hit>();
			auto hit2 = std::make_shared<Hit>();

			initialize_hit(hit1.get(), ray, t1);
			initialize_hit(hit2.get(), ray, t2);

			hits.push_back(hit1);
			hits.push_back(hit2);

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