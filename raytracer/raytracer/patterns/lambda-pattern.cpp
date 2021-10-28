#include "patterns/lambda-pattern.h"


namespace
{
    class LambdaPattern2DImplementation : public patterns::Pattern2DImplementation
    {
    public:
        LambdaPattern2DImplementation(std::function<bool(const math::Point2D&)> function)
            : m_function(function)
        {
            // NOP
        }

        bool at(const math::Point2D& point) const override
        {
            return m_function(point);
        }

    private:
        std::function<bool(const math::Point2D&)> m_function;
    };

    class LambdaPattern3DImplementation : public patterns::Pattern3DImplementation
    {
    public:
        LambdaPattern3DImplementation(std::function<bool(const math::Point3D&)> function)
            : m_function(function)
        {
            // NOP
        }

        bool at(const math::Point3D& point) const override
        {
            return m_function(point);
        }

    private:
        std::function<bool(const math::Point3D&)> m_function;
    };
}

patterns::Pattern2D patterns::make_pattern(std::function<bool(const math::Point2D&)> function)
{
    return Pattern2D(std::make_shared<LambdaPattern2DImplementation>(function));
}

patterns::Pattern3D patterns::make_pattern(std::function<bool(const math::Point3D&)> function)
{
    return Pattern3D(std::make_shared<LambdaPattern3DImplementation>(function));
}
