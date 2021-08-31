#pragma once

#include "math/point.h"
#include "patterns/pattern.h"
#include <functional>


namespace patterns
{
    namespace _private_
    {
        class LambdaPattern2DImplementation : public Pattern2DImplementation
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

        class LambdaPattern3DImplementation : public Pattern3DImplementation
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

    inline Pattern2D make_pattern(std::function<bool(const math::Point2D&)> function)
    {
        return Pattern2D(std::make_shared<_private_::LambdaPattern2DImplementation>(function));
    }

    inline Pattern3D make_pattern(std::function<bool(const math::Point3D&)> function)
    {
        return Pattern3D(std::make_shared<_private_::LambdaPattern3DImplementation>(function));
    }
}
