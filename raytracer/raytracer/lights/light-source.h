#pragma once

#include "lights/light-ray.h"
#include "math/point.h"
#include <vector>
#include <memory>

namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            class LightSourceImplementation
            {
            public:
                virtual std::vector<LightRay> lightrays_to(const math::Point3D&) const = 0;
            };
        }        
    }

    class LightSource
    {
    public:
        LightSource()
            : LightSource(nullptr) { }

        explicit LightSource(std::shared_ptr<lights::_private_::LightSourceImplementation> implementation)
            : m_implementation(implementation) { }

        lights::_private_::LightSourceImplementation* operator ->() const
        {
            return m_implementation.get();
        }

    private:
        std::shared_ptr<lights::_private_::LightSourceImplementation> m_implementation;
    };
}