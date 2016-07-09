#pragma once

#include "rendering/light-ray.h"
#include "math/point3d.h"
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

        class LightSource
        {
        public:
            LightSource(std::shared_ptr<_private_::LightSourceImplementation> implementation)
                : m_implementation(implementation) { }

            _private_::LightSourceImplementation* operator ->() const
            {
                return m_implementation.get();
            }

        private:
            std::shared_ptr<_private_::LightSourceImplementation> m_implementation;
        };
    }
}