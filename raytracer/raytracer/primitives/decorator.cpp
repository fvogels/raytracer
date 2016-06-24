#include "Decorator.h"
#include <assert.h>

using namespace raytracer;
using namespace math;


raytracer::primitives::Decorator::Decorator(Material material, Primitive child)
	: material(material), child(child)
{
	assert(material);
	assert(child);
}

bool raytracer::primitives::Decorator::find_hit(const Ray& ray, Hit* hit) const
{
	Material old_material = hit->material;
	hit->material = Material();

	bool result = child->find_hit(ray, hit);

	if (result && !hit->material)
	{
		hit->material = this->material;
	}
	else
	{
		hit->material = old_material;
	}

	return result;
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::Decorator::hits(const math::Ray& ray) const
{
	auto hits = this->child->hits(ray);

	for (auto hit : hits)
	{
		if (!hit->material)
		{
			hit->material = this->material;
		}
	}

	return hits;
}