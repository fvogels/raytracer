#pragma once

#include "math/rectangle2d.h"
#include <functional>
#include <memory>


namespace raytracer
{
    namespace samplers
    {
        namespace _private_
        {
            class SamplerImplementation
            {
            public:
                virtual void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const = 0;
            };
        }

        class Sampler
        {
        public:
            Sampler() : m_implementation(nullptr) { }

            Sampler(std::shared_ptr<_private_::SamplerImplementation> implementation)
                : m_implementation(implementation) { }

            _private_::SamplerImplementation* operator ->() const
            {
                return m_implementation.get();
            }

        private:
            std::shared_ptr<_private_::SamplerImplementation> m_implementation;
        };
    }
    
}