#include "materials/materials.h"
#include "math/function.h"
#include "math/functions/checkerboard.h"
#include "math/functions/bool_mapper.h"

using namespace math;
using namespace raytracer;

std::shared_ptr<Material2D> raytracer::materials::checkered(const color& c1, const color& c2)
{
	auto bool_mapper = math::functions::BoolMapper<color>(c1, c2);
	auto texture = std::make_shared<math::functions::Checkerboard<math::functions::BoolMapper<color>>>(bool_mapper);

	return std::make_shared<SimpleMaterial2D>(texture);
}