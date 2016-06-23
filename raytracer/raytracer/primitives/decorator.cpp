#include "Decorator.h"
#include <assert.h>

using namespace raytracer;
using namespace math;

raytracer::primitives::Decorator::Decorator(std::shared_ptr<Material> material, std::shared_ptr<Primitive> child)
	: material(material), child(child)
{
	assert(material != nullptr);
	assert(child != nullptr);
}

bool raytracer::primitives::Decorator::find_hit(const Ray& ray, Hit* hit) const
{
	auto old_material = hit->material;
	hit->material = this->material;
	
	bool result = child->find_hit(ray, hit);

	hit->material = old_material;

	return result;
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::Decorator::hits(const math::Ray& ray, const Context& context) const
{
	Context updated_context = context;
	updated_context.material = this->material;

	return this->child->hits(ray, updated_context);
}