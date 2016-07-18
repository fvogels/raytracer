#include "primitives/group.h"

using namespace raytracer;
using namespace raytracer::primitives;


raytracer::primitives::_private_::Group::Group(Primitive child, unsigned id)
    : m_child(child), m_id(id)
{
    // NOP
}

bool raytracer::primitives::_private_::Group::find_hit(const math::Ray& ray, Hit* hit) const
{
    if (m_child->find_hit(ray, hit))
    {
        if (hit->group_id == MISSING_ID)
        {
            hit->group_id = m_id;
        }

        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::Group::hits(const math::Ray& ray) const
{
    auto hit_list = m_child->hits(ray);

    for (auto& hit : hit_list)
    {
        if (hit->group_id == MISSING_ID)
        {
            hit->group_id = m_id;
        }
    }

    return hit_list;
}

math::Box raytracer::primitives::_private_::Group::bounding_box() const
{
    return m_child->bounding_box();
}