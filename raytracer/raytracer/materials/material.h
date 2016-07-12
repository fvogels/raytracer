#pragma once

#include "imaging/color.h"
#include "math/point2d.h"
#include "primitives/hit-position.h"
#include "materials/brdf.h"
#include "materials/material-properties.h"
#include <assert.h>
#include <memory>


namespace raytracer
{
    namespace materials
    {
        namespace _private_
        {
            class MaterialImplementation
            {
            public:
                virtual MaterialProperties at(const HitPosition&) const = 0;
            };

            class Material2D : public MaterialImplementation
            {
            public:
                MaterialProperties at(const HitPosition&) const override;

            protected:
                virtual MaterialProperties at(const math::Point2D&) const = 0;
            };

            class Material3D : public MaterialImplementation
            {
            public:
                MaterialProperties at(const HitPosition&) const override;

            protected:
                virtual MaterialProperties at(const math::Point3D&) const = 0;
            };
        }
    }    

    class Material
    {
    public:
        Material(std::shared_ptr<materials::_private_::MaterialImplementation> impl = nullptr)
            : m_impl(impl) { }

        operator bool() const
        {
            return m_impl != nullptr;
        }

        materials::_private_::MaterialImplementation* operator ->() const
        {
            return m_impl.get();
        }

    private:
        std::shared_ptr<materials::_private_::MaterialImplementation> m_impl;
    };
}