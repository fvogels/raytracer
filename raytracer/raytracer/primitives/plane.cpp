#include "primitives/plane.h"

using namespace raytracer;
using namespace math;


bool raytracer::primitives::PlaneXY::find_hit(const Ray& ray, Hit* hit) const
{
	assert(hit != nullptr);

	const Vector3D normal(0, 0, 1);
	double denom = ray.direction.dot(normal);

	if (denom == approx<double>(0))
	{
		return false;
	}
	else
	{
		double numer = -((ray.origin - Point3D(0, 0, 0)).dot(normal));
		double t = numer / denom;

		if (0 < t && t < hit->t)
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x, hit->position.y);
			hit->normal = ray.origin.z > 0 ? normal : -normal;

			return true;
		}
		else
		{
			return false;
		}
	}
}

bool raytracer::primitives::PlaneXZ::find_hit(const Ray& ray, Hit* hit) const
{
	assert(hit != nullptr);

	const Vector3D normal(0, 1, 0);
	double denom = ray.direction.dot(normal);

	if (denom == approx<double>(0))
	{
		return false;
	}
	else
	{
		double numer = -((ray.origin - Point3D(0, 0, 0)).dot(normal));
		double t = numer / denom;

		if (0 < t && t < hit->t)
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x, hit->position.z);
			hit->normal = ray.origin.y > 0 ? normal : -normal;

			return true;
		}
		else
		{
			return false;
		}
	}
}

bool raytracer::primitives::PlaneYZ::find_hit(const Ray& ray, Hit* hit) const
{
	assert(hit != nullptr);

	const Vector3D normal(1, 0, 0);
	double denom = ray.direction.dot(normal);

	if (denom == approx<double>(0))
	{
		return false;
	}
	else
	{
		double numer = -((ray.origin - Point3D(0, 0, 0)).dot(normal));
		double t = numer / denom;

		if (0 < t && t < hit->t)
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.y, hit->position.z);
			hit->normal = ray.origin.x > 0 ? normal : -normal;

			return true;
		}
		else
		{
			return false;
		}
	}
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::CoordinatePlane::hits(const math::Ray& ray) const
{
	auto hit = std::make_shared<Hit>();

	if (find_hit(ray, hit.get()))
	{
		return std::vector<std::shared_ptr<Hit>> { hit };
	}
	else
	{
		return std::vector<std::shared_ptr<Hit>>();
	}
}