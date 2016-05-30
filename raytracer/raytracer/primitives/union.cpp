#include "Union.h"

using namespace Raytracer;
using namespace math;

bool Union::find_hit(const Ray& ray, Hit* hit) const
{
	bool found_hit = false;

	for (const auto& child : this->children)
	{
		found_hit = child->find_hit(ray, hit) || found_hit;
	}

	return found_hit;
}