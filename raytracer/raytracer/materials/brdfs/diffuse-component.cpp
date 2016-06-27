#include "materials/brdfs/diffuse-component.h"
#include <algorithm>
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace raytracer::brdfs;
using namespace imaging;


raytracer::brdfs::_private_::DiffuseComponent::DiffuseComponent(const color& c)
    : m_color(c)
{
    // NOP
}

color raytracer::brdfs::_private_::DiffuseComponent::evaluate(
    const math::Vector3D& incoming_direction,
    const imaging::color& incoming_color,
    const math::Vector3D& normal,
    const math::Vector3D& outgoing_direction) const
{
    assert(incoming_direction.is_unit());
    assert(normal.is_unit());
    assert(outgoing_direction.is_unit());

    double cosine = -incoming_direction.dot(normal);
    double reflectivity = std::max(0.0, cosine);

    return m_color * reflectivity;
}

BRDF raytracer::brdfs::diffuse_component(const color& c)
{
    return BRDF(std::make_shared<_private_::DiffuseComponent>(c));
}