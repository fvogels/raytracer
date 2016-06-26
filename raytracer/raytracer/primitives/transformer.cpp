#include "primitives/transformer.h"
#include <algorithm>

using namespace math;
using namespace raytracer;


bool raytracer::primitives::Transformer::find_hit(const Ray& ray, Hit* hit) const
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

std::vector<std::shared_ptr<Hit>> raytracer::primitives::Transformer::hits(const math::Ray& ray) const
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
