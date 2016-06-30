#include "materials/brdfs/specular-component.h"
#include <algorithm>
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace raytracer::brdfs;
using namespace imaging;


raytracer::brdfs::_private_::SpecularComponent::SpecularComponent(const color& c, double exponent)
    : m_color(c), m_exponent(exponent)
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
    assert(outgoing_direction.is_unit());

    auto reflected_incoming_direction = incoming_direction.reflect_by(normal);
    double cos_between_reflected_and_outgoing = reflected_incoming_direction.dot(outgoing_direction);
    
    if (cos_between_reflected_and_outgoing > 0)
    {
        return incoming_color * m_color * std::pow(cos_between_reflected_and_outgoing, m_exponent);
    }
    else
    {
        return colors::black();
    }
}

BRDF raytracer::brdfs::specular_component(const color& c, double exponent)
{
    return BRDF(std::make_shared<_private_::SpecularComponent>(c, exponent));
}