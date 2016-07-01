#include "primitives/decorator.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


raytracer::primitives::_private_::Decorator::Decorator(Material material, Primitive child)
    : material(material), child(child)
{
    assert(material);
    assert(child);
}

bool raytracer::primitives::_private_::Decorator::find_hit(const Ray& ray, Hit* hit) const
{
    Material old_material = hit->material;
    hit->material = Material();

    bool result = child->find_hit(ray, hit);

    if (result)
    {
        if (!hit->material)
        {
            hit->material = this->material;
        }
    }
    else
    {
        hit->material = old_material;
    }
    
    assert(!result || hit->material);

    return result;
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::Decorator::hits(const math::Ray& ray) const
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

Primitive raytracer::primitives::decorate(Material material, Primitive child)
{
    return Primitive(std::make_shared<raytracer::primitives::_private_::Decorator>(material, child));
}
