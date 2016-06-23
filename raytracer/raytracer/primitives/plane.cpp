#include "primitives/plane.h"

using namespace raytracer;
using namespace math;


namespace
{
	void initialize_hit_for_xy_plane(Hit* hit, const Ray& ray, double t)
	{
		hit->t = t;
		hit->position = ray.at(hit->t);
		hit->local_position.xyz = hit->position;
		hit->local_position.uv = Point2D(hit->position.x, hit->position.y);
		hit->normal = Vector3D(0, 0, 1);

		assert(hit->position.z == approx(0));
		assert(hit->normal.is_unit());
	}
}

bool raytracer::primitives::PlaneXY::find_hit(const Ray& ray, Hit* hit) const
{
	assert(hit != nullptr);

	const Vector3D normal(0, 0, 1);
	double denom = ray.direction.dot(normal);

	if (denom == approx(0))
	{
		return false;
	}
	else
	{
		double numer = -((ray.origin - Point3D(0,0,0)).dot(normal));
		double t = numer / denom;

		if (t < hit->t)
		{
			initialize_hit_for_xy_plane(hit, ray, t);

			return true;
		}
		else
		{
			return false;
		}
	}
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::PlaneXY::hits(const math::Ray& ray) const
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