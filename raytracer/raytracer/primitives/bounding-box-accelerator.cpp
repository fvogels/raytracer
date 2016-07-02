#include "primitives/bounding_box_accelerator.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


raytracer::primitives::_private_::BoundingBoxAccelerator::BoundingBoxAccelerator(Primitive child)
    : m_child(child), m_bounding_box(child->bounding_box())
{
    // NOP
}

bool raytracer::primitives::_private_::BoundingBoxAccelerator::find_hit(const math::Ray& ray, Hit* hit) const
{
    if (m_bounding_box.hits(ray))
    {
        return m_child->find_hit(ray, hit);
    }
    else
    {
        return false;
    }
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::BoundingBoxAccelerator::hits(const math::Ray& ray) const
{
    if (m_bounding_box.hits(ray))
    {
        return m_child->hits(ray);
    }
    else
    {
        return std::vector<std::shared_ptr<Hit>>();
    }
}

math::Box raytracer::primitives::_private_::BoundingBoxAccelerator::bounding_box() const
{
    return m_bounding_box;
}

