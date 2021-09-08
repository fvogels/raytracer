#pragma once

#include "patterns/pattern.h"
#include <functional>


namespace patterns
{
    namespace _private_
    {
        class LambdaPattern2DImplementation : public Pattern2DImplementation
        {
        public:
            LambdaPattern2DImplementation(std::function<bool(const math::Point2D&)> function);

            bool at(const math::Point2D& point) const override;

        private:
            std::function<bool(const math::Point2D&)> m_function;
        };

        class LambdaPattern3DImplementation : public Pattern3DImplementation
        {
        public:
            LambdaPattern3DImplementation(std::function<bool(const math::Point3D&)> function);

            bool at(const math::Point3D& point) const override;

        private:
            std::function<bool(const math::Point3D&)> m_function;
        };
    }

    Pattern2D make_pattern(std::function<bool(const math::Point2D&)> function);
    Pattern3D make_pattern(std::function<bool(const math::Point3D&)> function);
}
