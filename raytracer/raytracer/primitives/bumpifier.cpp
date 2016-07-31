#include "primitives/bumpifier.h"
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


bool raytracer::primitives::_private_::Bumpifier::find_hit(const Ray& ray, Hit* hit) const
{
    if (m_perturbee->find_hit(ray, hit))
    {
        perturb(hit);

        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::Bumpifier::hits(const math::Ray& ray) const
{
    auto hits = m_perturbee->hits(ray);

    for (auto& hit : hits)
    {
        perturb(hit.get());
    }

    return hits;
}

void raytracer::primitives::_private_::Bumpifier::perturb(Hit* hit) const
{
    hit->normal = (hit->normal + m_normal_perturbator(hit->local_position.xyz)).normalized();
}

math::Box raytracer::primitives::_private_::Bumpifier::bounding_box() const
{
    return m_perturbee->bounding_box();
}

Primitive raytracer::primitives::bumpify(math::Function<math::Vector3D(const math::Point3D&)> function, Primitive primitive)
{
    return Primitive(std::make_shared<raytracer::primitives::_private_::Bumpifier>(function, primitive));
}