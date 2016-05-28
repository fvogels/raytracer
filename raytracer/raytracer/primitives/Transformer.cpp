#include "primitives/Transformer.h"

using namespace math;

bool raytracer::Transformer::find_hit(const ray& r, Hit* hit) const
{
	ray transformed_ray = r.transform(this->transformer.inverse_transformation_matrix);

	return this->transformee->find_hit(transformed_ray, hit);
}