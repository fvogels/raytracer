#include "primitives/transformer.h"
#include "math/misc.h"
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;

namespace
{
    class Transformer : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        Transformer(const math::Transformation& transformer, Primitive transformee)
            : transformer(transformer), transformee(transformee) { }

        bool find_hit(const Ray& ray, Hit* hit) const override
        {
            Ray transformed_ray = ray.transform(this->transformer.inverse_Transformation_matrix);

            if (this->transformee->find_hit(transformed_ray, hit))
            {
                hit->position = this->transformer.transformation_matrix * hit->position;
                hit->normal = (this->transformer.transformation_matrix * hit->normal).normalized();

                return true;
            }
            else
            {
                return false;
            }
        }

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray& ray) const override
        {
            Ray transformed_ray = ray.transform(this->transformer.inverse_Transformation_matrix);

            auto hits = this->transformee->hits(transformed_ray);

            for (auto& hit : hits)
            {
                hit->position = this->transformer.transformation_matrix * hit->position;
                hit->normal = (this->transformer.transformation_matrix * hit->normal).normalized();
            }

            return hits;
        }

        math::Box bounding_box() const override
        {
            auto box = transformee->bounding_box();

#define AUX(I, J, K)       Point3D p ## I ## J ## K = this->transformer.transformation_matrix * box.corner<I, J, K>()
            AUX(0, 0, 0);
            AUX(0, 0, 1);
            AUX(0, 1, 0);
            AUX(0, 1, 1);
            AUX(1, 0, 0);
            AUX(1, 0, 1);
            AUX(1, 1, 0);
            AUX(1, 1, 1);
#undef AUX

            double min_x = math::minimum(p000.x(), p001.x(), p010.x(), p011.x(), p100.x(), p101.x(), p110.x(), p111.x());
            double max_x = math::maximum(p000.x(), p001.x(), p010.x(), p011.x(), p100.x(), p101.x(), p110.x(), p111.x());

            double min_y = math::minimum(p000.y(), p001.y(), p010.y(), p011.y(), p100.y(), p101.y(), p110.y(), p111.y());
            double max_y = math::maximum(p000.y(), p001.y(), p010.y(), p011.y(), p100.y(), p101.y(), p110.y(), p111.y());

            double min_z = math::minimum(p000.z(), p001.z(), p010.z(), p011.z(), p100.z(), p101.z(), p110.z(), p111.z());
            double max_z = math::maximum(p000.z(), p001.z(), p010.z(), p011.z(), p100.z(), p101.z(), p110.z(), p111.z());

            Point3D lower_corner = point(min_x, min_y, min_z);
            Point3D upper_corner = point(max_x, max_y, max_z);

            return Box::from_raw_corners(lower_corner, upper_corner);
        }

    private:
        math::Transformation transformer;
        Primitive transformee;
    };
}

Primitive raytracer::primitives::transform(const math::Transformation& transformation, Primitive transformee)
{
    return Primitive(std::make_shared<Transformer>(transformation, transformee));
}

Primitive raytracer::primitives::translate(const math::Vector3D& v, Primitive transformee)
{
    return transform(math::transformations::translation(v), transformee);
}

Primitive raytracer::primitives::scale(double x, double y, double z, Primitive transformee)
{
    return transform(math::transformations::scale(x, y, z), transformee);
}

Primitive raytracer::primitives::rotate_around_x(math::Angle angle, Primitive transformee)
{
    return transform(math::transformations::rotate_x(angle), transformee);
}

Primitive raytracer::primitives::rotate_around_y(math::Angle angle, Primitive transformee)
{
    return transform(math::transformations::rotate_y(angle), transformee);
}

Primitive raytracer::primitives::rotate_around_z(math::Angle angle, Primitive transformee)
{
    return transform(math::transformations::rotate_z(angle), transformee);
}

Primitive raytracer::primitives::center(const Point3D& center, Primitive primitive)
{
    Point3D primitive_center = primitive->bounding_box().center();

    return translate(center - primitive_center, primitive);
}