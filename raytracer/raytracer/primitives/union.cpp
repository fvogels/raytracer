#include "primitives/union.h"
#include <algorithm>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


raytracer::primitives::_private_::Union::Union(std::vector<Primitive>& children)
    : children(children)
{
    // NOP
}

bool raytracer::primitives::_private_::Union::find_hit(const Ray& ray, Hit* hit) const
{
    bool found_hit = false;

    for (const auto& child : this->children)
    {
        found_hit = child->find_hit(ray, hit) || found_hit;
    }

    return found_hit;
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::Union::hits(const math::Ray& ray) const
{
    std::vector<std::shared_ptr<Hit>> hits;

    for (const auto& child : this->children)
    {
        for (auto hit : child->hits(ray))
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

math::Box raytracer::primitives::_private_::Union::bounding_box() const
{
    Box result = Box::empty();

    for (auto child : this->children)
    {
        Box child_box = child->bounding_box();
        result = result.merge(child_box);
    }

    return result;
}

Primitive raytracer::primitives::group(std::vector<Primitive>& children)
{
    return Primitive(std::make_shared<_private_::Union>(children));
}