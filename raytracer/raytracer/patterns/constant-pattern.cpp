#include "patterns/constant-pattern.h"


namespace
{
    class ConstantPattern2D : public patterns::Pattern2DImplementation
    {
    public:
        ConstantPattern2D(bool constant)
            : m_constant(constant)
        {
            // NOP
        }

        bool at(const math::Point2D& point) const override
        {
            return m_constant;
        }

    private:
        bool m_constant;
    };

    class ConstantPattern3D : public patterns::Pattern3DImplementation
    {
    public:
        ConstantPattern3D(bool constant)
            : m_constant(constant)
        {
            // NOP
        }

        bool at(const math::Point3D& point) const override
        {
            return m_constant;
        }

    private:
        bool m_constant;
    };
}

patterns::Pattern2D patterns::constant2d(bool constant)
{
    return patterns::Pattern2D(std::make_shared<ConstantPattern2D>(constant));
}

patterns::Pattern3D patterns::constant3d(bool constant)
{
    return patterns::Pattern3D(std::make_shared<ConstantPattern3D>(constant));
}
