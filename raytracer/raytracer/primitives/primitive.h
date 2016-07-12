#pragma once

#include "primitives/hit.h"
#include "math/ray.h"
#include "math/box.h"
#include <iostream>
#include <vector>
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        class PrimitiveImplementation
        {
        public:
            virtual bool find_hit(const math::Ray&, Hit*) const = 0;
            virtual std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const = 0;
            virtual math::Box bounding_box() const = 0;
        };
    }

    class Primitive
    {
    public:
        Primitive(std::shared_ptr<primitives::PrimitiveImplementation> impl = nullptr)
            : m_impl(impl) { }

        primitives::PrimitiveImplementation* operator ->()
        {
            return m_impl.get();
        }

        primitives::PrimitiveImplementation* operator ->() const
        {
            return m_impl.get();
        }

        bool operator ==(const Primitive& p) const
        {
            // TODO
            throw std::runtime_error("Cannot compare primitives");
        }

        bool operator !=(const Primitive& p) const
        {
            return !(*this == p);
        }

        operator bool() const
        {
            return m_impl != nullptr;
        }

    private:
        std::shared_ptr<primitives::PrimitiveImplementation> m_impl;
    };

    inline std::ostream& operator <<(std::ostream& out, const Primitive&)
    {
        // TODO
        return out << "<primitive>";
    }
}