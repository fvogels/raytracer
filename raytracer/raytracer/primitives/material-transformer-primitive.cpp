#include "primitives/material-transformer-primitive.h"
#include "math/transformation-matrices.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class MaterialTransformer : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        MaterialTransformer(Primitive child)
            : m_child(child)
        {
            // NOP
        }

        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            if (m_child->find_first_positive_hit(ray, hit))
            {
                transform_hit(hit);

                return true;
            }
            else
            {
                return false;
            }
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            auto hits = this->m_child->find_all_hits(ray);

            for (auto hit : hits)
            {
                transform_hit(hit.get());
            }

            return hits;
        }

        math::Box bounding_box() const override
        {
            return m_child->bounding_box();
        }

    protected:
        virtual void transform_hit(Hit* hit) const = 0;

        Primitive m_child;
    };

    class MaterialTransformer2D : public MaterialTransformer
    {
    public:
        MaterialTransformer2D(const Matrix3D& transformation_matrix, Primitive child)
            : MaterialTransformer(child), m_transformation_matrix(transformation_matrix)
        {
            // NOP
        }

    private:
        void transform_hit(Hit* hit) const
        {
            hit->local_position.uv = m_transformation_matrix * hit->local_position.uv;
        }

        Matrix3D m_transformation_matrix;
        Primitive m_child;
    };

    class MaterialTransformer3D : public MaterialTransformer
    {
    public:
        MaterialTransformer3D(const Matrix4D& transformation_matrix, Primitive child)
            : MaterialTransformer(child), m_transformation_matrix(transformation_matrix)
        {
            // NOP
        }

    private:
        void transform_hit(Hit* hit) const
        {
            hit->local_position.xyz = m_transformation_matrix * hit->local_position.xyz;
        }

        Matrix4D m_transformation_matrix;
        Primitive m_child;
    };
}

Primitive raytracer::primitives::transform_material2d(const Matrix3D& transformation_matrix, Primitive child)
{
    return Primitive(std::make_shared<MaterialTransformer2D>(transformation_matrix, child));
}

Primitive raytracer::primitives::transform_material3d(const Matrix4D& transformation_matrix, Primitive child)
{
    return Primitive(std::make_shared<MaterialTransformer3D>(transformation_matrix, child));
}

Primitive raytracer::primitives::translate_material2d(const Vector2D& translation_vector, Primitive child)
{
    return transform_material2d(math::transformation_matrices::translation(translation_vector), child);
}

Primitive raytracer::primitives::translate_material3d(const Vector3D& translation_vector, Primitive child)
{
    return transform_material3d(math::transformation_matrices::translation(translation_vector), child);
}

Primitive raytracer::primitives::scale_material2d(double sx, double sy, Primitive child)
{
    return transform_material2d(math::transformation_matrices::scaling(sx, sy), child);
}

Primitive raytracer::primitives::scale_material3d(double sx, double sy, double sz, Primitive child)
{
    return transform_material3d(math::transformation_matrices::scaling(sx, sy, sz), child);
}

Primitive raytracer::primitives::rotate_material(math::Angle angle, Primitive child)
{
    return transform_material2d(math::transformation_matrices::rotation(angle), child);
}

Primitive raytracer::primitives::rotate_material_around_x(math::Angle angle, Primitive child)
{
    return transform_material3d(math::transformation_matrices::rotation_around_x(angle), child);
}

Primitive raytracer::primitives::rotate_material_around_y(math::Angle angle, Primitive child)
{
    return transform_material3d(math::transformation_matrices::rotation_around_y(angle), child);
}

Primitive raytracer::primitives::rotate_material_around_z(math::Angle angle, Primitive child)
{
    return transform_material3d(math::transformation_matrices::rotation_around_z(angle), child);
}
