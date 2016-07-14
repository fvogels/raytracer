#include "materials/material.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::materials;


namespace
{
    class FunctionMaterial2D : public _private_::Material2D
    {
    public:
        FunctionMaterial2D(math::Function<MaterialProperties, const Point2D&> function)
            : m_function(function) 
        {
            // NOP
        }

    protected:
        MaterialProperties at(const math::Point2D& p) const override
        {
            return m_function(p);
        }

    private:
        math::Function<MaterialProperties, const Point2D&> m_function;
    };

    class FunctionMaterial3D : public _private_::Material3D
    {
    public:
        FunctionMaterial3D(math::Function<MaterialProperties, const Point3D&> function)
            : m_function(function)
        {
            // NOP
        }

    protected:
        MaterialProperties at(const math::Point3D& p) const override
        {
            return m_function(p);
        }

    private:
        math::Function<MaterialProperties, const Point3D&> m_function;
    };
}

MaterialProperties raytracer::materials::_private_::Material2D::at(const HitPosition& hp) const
{
    return at(hp.uv);
}

MaterialProperties raytracer::materials::_private_::Material3D::at(const HitPosition& hp) const
{
    return at(hp.xyz);
}

Material raytracer::make_2d_material(math::Function<MaterialProperties, const Point2D&> function)
{
    return Material(std::make_shared<FunctionMaterial2D>(function));
}

Material raytracer::make_3d_material(math::Function<MaterialProperties, const Point3D&> function)
{
    return Material(std::make_shared<FunctionMaterial3D>(function));
}