#include "Union.h"

using namespace raytracer;
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