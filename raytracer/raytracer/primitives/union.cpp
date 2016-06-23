#include "Union.h"
#include <algorithm>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


raytracer::primitives::Union::Union(std::vector<std::shared_ptr<Primitive>>& children)
	: children(children)
{
	// NOP
}

bool raytracer::primitives::Union::find_hit(const Ray& ray, Hit* hit) const
{
	bool found_hit = false;

	for (const auto& child : this->children)
	{
		found_hit = child->find_hit(ray, hit) || found_hit;
	}

	return found_hit;
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::Union::hits(const math::Ray& ray, const Context& context) const
{
	std::vector<std::shared_ptr<Hit>> hits;

	for (const auto& child : this->children)
	{
		for (auto hit : child->hits(ray, context))
		{
			hits.push_back(hit);
		}
	}

	std::sort(hits.begin(), hits.end(), [](const std::shared_ptr<Hit>& h1, const std::shared_ptr<Hit>& h2)
	{
		return h1->t < h2->t;
	});

	return hits;
}