#include "materials/brdfs/specular-component.h"
#include <algorithm>
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace raytracer::brdfs;
using namespace imaging;


raytracer::brdfs::_private_::SpecularComponent::SpecularComponent(const color& c)
    : m_color(c)
{
    // NOP
}

color raytracer::brdfs::_private_::SpecularComponent::evaluate(
    const math::Vector3D& incoming_direction,
    const imaging::color& incoming_color,
    const math::Vector3D& normal,
    const math::Vector3D& outgoing_direction) const
{
    assert(incoming_direction.is_unit());
    assert(normal.is_unit());
    assert(out.is_unit());

    auto reflected_incoming_direction = incoming_direction.reflect_by(normal);
    double cos_between_reflected_and_outgoing = reflected_incoming_direction.dot(outgoing_direction);
    double reflectivity = std::max(cos_between_reflected_and_outgoing, 0.0);

    return reflectivity * m_color;
}

BRDF raytracer::brdfs::specular_component(const color& c)
{
    return BRDF(std::make_shared<_private_::SpecularComponent>(c));
}