#include "primitives/Transformer.h"

using namespace math;

bool Raytracer::Transformer::find_hit(const Ray& ray, Hit* hit) const
{
	Ray transformed_Ray = ray.transform(this->transformer.inverse_transformation_matrix);

	if (this->transformee->find_hit(transformed_Ray, hit))
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