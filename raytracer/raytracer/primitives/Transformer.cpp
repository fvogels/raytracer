#include "primitives/Transformer.h"

using namespace math;

bool raytracer::Transformer::find_hit(const ray& r, Hit* hit) const
{
	ray transformed_ray = r.transform(this->transformer.inverse_transformation_matrix);

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