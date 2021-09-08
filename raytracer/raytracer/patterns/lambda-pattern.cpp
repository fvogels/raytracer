#include "patterns/lambda-pattern.h"


patterns::_private_::LambdaPattern2DImplementation::LambdaPattern2DImplementation(std::function<bool(const math::Point2D&)> function)
    : m_function(function)
{
    // NOP
}

bool patterns::_private_::LambdaPattern2DImplementation::at(const math::Point2D& point) const
{
    return m_function(point);
}

patterns::_private_::LambdaPattern3DImplementation::LambdaPattern3DImplementation(std::function<bool(const math::Point3D&)> function)
    : m_function(function)
{
    // NOP
}

bool patterns::_private_::LambdaPattern3DImplementation::at(const math::Point3D& point) const
{
    return m_function(point);
}

patterns::Pattern2D patterns::make_pattern(std::function<bool(const math::Point2D&)> function)
{
    return Pattern2D(std::make_shared<_private_::LambdaPattern2DImplementation>(function));
}

patterns::Pattern3D patterns::make_pattern(std::function<bool(const math::Point3D&)> function)
{
    return Pattern3D(std::make_shared<_private_::LambdaPattern3DImplementation>(function));
}
