#include "Decorator.h"
#include <assert.h>

using namespace Raytracer;
using namespace math;

Decorator::Decorator(std::shared_ptr<const Material3D> material, std::shared_ptr<const Primitive> child)
	: material(material), child(child)
{
	assert(material != nullptr);
	assert(child != nullptr);
}

bool Decorator::find_hit(const Ray& ray, Hit* hit) const
{
	if (child->find_hit(ray, hit))
	{
		hit->c = material->at(hit->position);

		return true;
	}
	else
	{
		return false;
	}
}