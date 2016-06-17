#include "primitives/transformer.h"

using namespace math;
using namespace raytracer;


bool raytracer::Transformer::find_hit(const Ray& ray, Hit* hit) const
{
	Ray transformed_Ray = ray.transform(this->transformer.inverse_Transformation_matrix);

	if (this->transformee->find_hit(transformed_Ray, hit))
	{
		hit->position = this->transformer.Transformation_matrix * hit->position;
		hit->normal = (this->transformer.Transformation_matrix * hit->normal).normalized();

		return true;
	}
	else
	{
		return false;
	}
}

std::shared_ptr<Transformer> raytracer::transform::transform(const math::Transformation& transformation, std::shared_ptr<const Primitive> transformee)
{
	return std::make_shared<Transformer>(transformation, transformee);
}

std::shared_ptr<Transformer> raytracer::transform::translate(const math::Vector3D& v, std::shared_ptr<const Primitive> transformee)
{
	return raytracer::transform::transform(math::translation(v), transformee);
}