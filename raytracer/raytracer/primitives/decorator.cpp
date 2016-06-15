#include "Decorator.h"
#include <assert.h>

using namespace raytracer;
using namespace math;

Decorator::Decorator(std::shared_ptr<Material3D> material, std::shared_ptr<Primitive> child)
	: material(material), child(child)
{
	assert(material != nullptr);
	assert(child != nullptr);
}

bool Decorator::find_hit(const Ray& ray, Hit* hit) const
{
	auto old_material = hit->material;
	hit->material = this->material;
	
	bool result = child->find_hit(ray, hit);

	hit->material = old_material;

	return result;
}