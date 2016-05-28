#include "Decorator.h"
#include <assert.h>

using namespace raytracer;
using namespace math;

Decorator::Decorator(std::shared_ptr<const Material3D> material, std::shared_ptr<const Primitive> child)
	: material(material), child(child)
{
	assert(material != nullptr);
	assert(child != nullptr);
}

bool Decorator::find_hit(const ray& r, Hit* hit) const
{
	if (child->find_hit(r, hit))
	{
		hit->c = material->at(hit->position);

		return true;
	}
	else
	{
		return false;
	}
}