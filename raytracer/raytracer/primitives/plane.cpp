#include "primitives/plane.h"

using namespace raytracer;
using namespace math;


namespace
{
	template<unsigned X, unsigned Y, unsigned Z>
	void initialize_hit(Hit* hit, const Ray& ray, double t)
	{
		hit->t = t;
		hit->position = ray.at(hit->t);
		hit->local_position.xyz = hit->position;
		hit->local_position.uv = Point2D(hit->position.x, hit->position.y);
		hit->normal = Vector3D(X, Y, Z);

		assert(X != 1 || hit->position.x == approx(0));
		assert(Y != 1 || hit->position.y == approx(0));
		assert(Z != 1 || hit->position.z == approx(0));
		assert(hit->normal.is_unit());
	}

	void initialize_hit_for_xy_plane(Hit* hit, const Ray& ray, double t)
	{
		initialize_hit<0, 0, 1>(hit, ray, t);
	}

	void initialize_hit_for_xz_plane(Hit* hit, const Ray& ray, double t)
	{
		initialize_hit<0, 1, 0>(hit, ray, t);
	}

	void initialize_hit_for_yz_plane(Hit* hit, const Ray& ray, double t)
	{
		initialize_hit<1, 0, 0>(hit, ray, t);
	}

	template<unsigned X, unsigned Y, unsigned Z>
	bool find_hit_with_plane(const Ray& ray, Hit* hit)
	{
		static_assert((X == 1 && Y == 0 && Z == 0) || (X == 0 && Y == 1 && Z == 0) || (X == 0 && Y == 0 && Z == 1), "(X, Y, Z) should denote a coordinate plan");

		assert(hit != nullptr);

		const Vector3D normal(X, Y, Z);
		double denom = ray.direction.dot(normal);

		if (denom == approx(0))
		{
			return false;
		}
		else
		{
			double numer = -((ray.origin - Point3D(0, 0, 0)).dot(normal));
			double t = numer / denom;

			if (t < hit->t)
			{
				initialize_hit<X, Y, Z>(hit, ray, t);

				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool raytracer::primitives::PlaneXY::find_hit(const Ray& ray, Hit* hit) const
{
	return find_hit_with_plane<0, 0, 1>(ray, hit);
}

bool raytracer::primitives::PlaneXZ::find_hit(const Ray& ray, Hit* hit) const
{
	return find_hit_with_plane<0, 1, 0>(ray, hit);
}

bool raytracer::primitives::PlaneYZ::find_hit(const Ray& ray, Hit* hit) const
{
	return find_hit_with_plane<1, 0, 0>(ray, hit);
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