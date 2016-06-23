#include "Decorator.h"
#include <assert.h>

using namespace raytracer;
using namespace math;

namespace
{
	void update_hit(Hit* hit, std::shared_ptr<Material> material)
	{
		if (hit->material == nullptr)
		{
			hit->material = material;
		}
	}
}

raytracer::primitives::Decorator::Decorator(std::shared_ptr<Material> material, std::shared_ptr<Primitive> child)
	: material(material), child(child)
{
	assert(material != nullptr);
	assert(child != nullptr);
}

bool raytracer::primitives::Decorator::find_hit(const Ray& ray, Hit* hit) const
{
	bool result = child->find_hit(ray, hit);

	if (result)
	{
		update_hit(hit, this->material);
	}

	return result;
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::Decorator::hits(const math::Ray& ray) const
{
	auto hits = this->child->hits(ray);

	for (auto hit : hits)
	{
		update_hit(hit.get(), material);
	}

	return hits;
}