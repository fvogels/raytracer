#include "primitives/transformer.h"
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


bool raytracer::primitives::_private_::Transformer::find_hit(const Ray& ray, Hit* hit) const
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

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::Transformer::hits(const math::Ray& ray) const
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

math::Box raytracer::primitives::_private_::Transformer::bounding_box() const
{
    // TODO
    abort();
}

Primitive raytracer::primitives::transform(const math::Transformation& transformation, Primitive transformee)
{
    return Primitive(std::make_shared<_private_::Transformer>(transformation, transformee));
}

Primitive raytracer::primitives::translate(const math::Vector3D& v, Primitive transformee)
{
    return transform(math::translation(v), transformee);
}

Primitive raytracer::primitives::scale(double x, double y, double z, Primitive transformee)
{
    return transform(math::scale(x, y, z), transformee);
}

Primitive raytracer::primitives::rotate_around_x(math::Angle angle, Primitive transformee)
{
    return transform(math::rotate_x(angle), transformee);
}

Primitive raytracer::primitives::rotate_around_y(math::Angle angle, Primitive transformee)
{
    return transform(math::rotate_y(angle), transformee);
}

Primitive raytracer::primitives::rotate_around_z(math::Angle angle, Primitive transformee)
{
    return transform(math::rotate_z(angle), transformee);
}

