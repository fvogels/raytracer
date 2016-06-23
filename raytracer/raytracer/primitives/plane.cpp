#include "primitives/plane.h"
#include "math/util.h"
#include "materials/material.h"
#include "materials/material2d.h"
#include "materials/material3d.h"
#include <assert.h>

using namespace raytracer;
using namespace math;

raytracer::primitives::Plane::Plane(const Point3D& point, const Vector3D& normal, const Vector3D& u)
	: point(point), normal(normal), u(u), v(normal.cross(u))
{
	assert(normal.is_unit());
	assert(u.is_unit());
	assert(u.is_perpendicular_on(v));
	assert(v.is_unit());
	assert(v.is_perpendicular_on(u));
	assert(v.is_perpendicular_on(normal));
}

bool raytracer::primitives::Plane::find_hit(const Ray& ray, Hit* hit) const
{
	assert(hit != nullptr);

	double denominator = ray.direction.dot(this->normal);

	if (denominator != approx(0))
	{
		double numerator = -(ray.origin - this->point).dot(this->normal);
		double t = numerator / denominator;

		if (0 <= t && t < hit->t)
		{
			hit->t = t;
			hit->normal = this->normal;
			hit->position = ray.at(t);

			auto material2d = std::dynamic_pointer_cast<Material2D>(hit->material);
			if (material2d != nullptr)
			{
				Vector3D r = hit->position - this->point;
				double u = r.dot(this->u);
				double v = r.dot(this->v);

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
	else
	{
		return false;
	}
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::Plane::hits(const math::Ray& ray, const Context& context) const
{
	double denominator = ray.direction.dot(this->normal);

	if (denominator != approx(0))
	{
		double numerator = -(ray.origin - this->point).dot(this->normal);
		double t = numerator / denominator;

		auto hit = std::make_shared<Hit>();

		hit->t = t;
		hit->normal = this->normal;
		hit->position = ray.at(t);

		auto material2d = std::dynamic_pointer_cast<Material2D>(context.material);
		if (material2d != nullptr)
		{
			Vector3D r = hit->position - this->point;
			double u = r.dot(this->u);
			double v = r.dot(this->v);

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

		return std::vector<std::shared_ptr<Hit>> { hit };
	}
	else
	{
		return std::vector<std::shared_ptr<Hit>>();
	}
}