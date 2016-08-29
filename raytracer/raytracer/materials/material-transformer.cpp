#include "materials/material-transformer.h"

using namespace raytracer;
using namespace math;


namespace
{
    class Material2DTransformer : public raytracer::materials::_private_::MaterialImplementation
    {
    public:
        Material2DTransformer(const math::Transformation2D& transformation, Material child)
            : m_child(child), m_transformation(transformation)
        {
            // NOP
        }

        MaterialProperties at(const HitPosition& hit_position) const override
        {
            auto transformed_uv = m_transformation.inverse_transformation_matrix * hit_position.uv;
            HitPosition transformed_hitposition{ transformed_uv, hit_position.xyz };

            return m_child->at(transformed_hitposition);
        }

    private:
        Material m_child;
        math::Transformation2D m_transformation;
    };

    class Material3DTransformer : public raytracer::materials::_private_::MaterialImplementation
    {
    public:
        Material3DTransformer(const math::Transformation3D& transformation, Material child)
            : m_child(child), m_transformation(transformation)
        {
            // NOP
        }

        MaterialProperties at(const HitPosition& hit_position) const override
        {
            auto transformed_xyz = m_transformation.inverse_transformation_matrix * hit_position.xyz;
            HitPosition transformed_hitposition{ hit_position.uv, transformed_xyz };

            return m_child->at(transformed_hitposition);
        }

    private:
        Material m_child;
        math::Transformation3D m_transformation;
    };
}

Material raytracer::materials::transform(const math::Transformation2D& transformation, Material material)
{
    return Material(std::make_shared<Material2DTransformer>(transformation, material));
}

Material raytracer::materials::transform(const math::Transformation3D& transformation, Material material)
{
    return Material(std::make_shared<Material3DTransformer>(transformation, material));
}

Material raytracer::materials::scale(double x, double y, Material material)
{
    return transform(math::transformations::scale(x, y), material);
}

Material raytracer::materials::translate(const math::Vector2D& v, Material material)
{
    return transform(math::transformations::translation(v), material);
}

Material raytracer::materials::rotate(math::Angle angle, Material material)
{
    return transform(math::transformations::rotate(angle), material);
}

Material raytracer::materials::scale(double x, double y, double z, Material material)
{
    return transform(math::transformations::scale(x, y, z), material);
}

Material raytracer::materials::translate(const math::Vector3D& v, Material material)
{
    return transform(math::transformations::translation(v), material);
}

Material raytracer::materials::rotate_around_x(math::Angle angle, Material material)
{
    return transform(math::transformations::rotate_x(angle), material);
}

Material raytracer::materials::rotate_around_y(math::Angle angle, Material material)
{
    return transform(math::transformations::rotate_y(angle), material);
}

Material raytracer::materials::rotate_around_z(math::Angle angle, Material material)
{
    return transform(math::transformations::rotate_z(angle), material);
}