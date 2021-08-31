#pragma once

#include "math/point.h"
#include <memory>


namespace math
{
    namespace functions
    {
        class Pattern2DImplementation
        {
        public:
            virtual bool at(const Point2D& point) const = 0;
        };

        class Pattern3DImplementation
        {
        public:
            virtual bool at(const Point3D& point) const = 0;
        };

        class Pattern2D
        {
        public:
            Pattern2D(std::shared_ptr<Pattern2DImplementation> implementation)
                : m_implementation(implementation)
            {
                // NOP
            }

            bool operator ()(const Point2D& point) const
            {
                return m_implementation->at(point);
            }

        private:
            std::shared_ptr<Pattern2DImplementation> m_implementation;
        };

        class Pattern3D
        {
        public:
            Pattern3D(std::shared_ptr<Pattern3DImplementation> implementation)
                : m_implementation(implementation)
            {
                // NOP
            }

            bool operator ()(const Point3D& point) const
            {
                return m_implementation->at(point);
            }

        private:
            std::shared_ptr<Pattern3DImplementation> m_implementation;
        };
    }
}