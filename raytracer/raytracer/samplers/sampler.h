#pragma once

#include "math/rectangle2d.h"
#include <functional>
#include <memory>
#include <vector>


namespace raytracer
{
    namespace samplers
    {
        namespace _private_
        {
            class SamplerImplementation
            {
            public:
                std::vector<math::Point2D> sample(const math::Rectangle2D&);

                virtual void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const = 0;
            };
        }        
    }
    
    /// <summary>
    /// Wrapper class for samplers. Access sampler members using -&gt;.
    /// </summary>
    class Sampler
    {
    public:
        explicit Sampler(std::shared_ptr<samplers::_private_::SamplerImplementation> implementation = nullptr)
            : m_implementation(implementation) { }

        samplers::_private_::SamplerImplementation* operator ->() const
        {
            return m_implementation.get();
        }

        operator bool() const
        {
            return m_implementation != nullptr;
        }

    private:
        std::shared_ptr<samplers::_private_::SamplerImplementation> m_implementation;
    };
}