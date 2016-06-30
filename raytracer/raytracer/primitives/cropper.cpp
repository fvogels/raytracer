#include "primitives/cropper.h"
#include <assert.h>
#include <algorithm>

using namespace raytracer;
using namespace raytracer::primitives;


raytracer::primitives::_private_::Cropper::Cropper(Primitive cropped, const math::Function<bool, const math::Point3D&> predicate)
    : m_cropped(cropped), m_predicate(predicate)
{
    assert(cropped);
    assert(predicate);
}

bool raytracer::primitives::_private_::Cropper::find_hit(const math::Ray& ray, Hit* hit) const
{
    auto hs = hits(ray);

    for (auto h : hs)
    {
        if (h->t > 0)
        {
            *hit = *h;
            return true;
        }
    }

    return false;
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::Cropper::hits(const math::Ray& ray) const
{
    auto hits = m_cropped->hits(ray);

    std::remove_if(hits.begin(), hits.end(), [this](std::shared_ptr<Hit> hit)
    {
        return !this->m_predicate(hit->position);
    });

    return hits;
}

Primitive raytracer::primitives::crop(Primitive cropped, math::Function<bool, const math::Point3D&> predicate)
{
    return Primitive(std::make_shared<_private_::Cropper>(cropped, predicate));
}