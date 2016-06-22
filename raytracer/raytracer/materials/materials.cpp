#include "materials/materials.h"
#include "math/function.h"
#include "math/functions/patterns.h"
#include "math/functions/noise.h"
#include "math/functions/bool-mapper.h"
#include "imaging/color-mapper.h"

using namespace math;
using namespace raytracer;


std::shared_ptr<Material> raytracer::materials::uniform(const color& c)
{
	return std::make_shared<UniformMaterial>(c);
}

std::shared_ptr<Material> raytracer::materials::checkered(const color& c1, const color& c2)
{
	auto bool_mapper = math::functions::bool_mapper(c1, c2);
	auto texture = math::functions::checkerboard();

	return std::make_shared<SimpleMaterial2D>(texture >> bool_mapper);
}

std::shared_ptr<Material> raytracer::materials::worley(const color& c1, const color& c2)
{
	auto color_mapper = imaging::color_mapping::grayscale();
	math::Function<double, const Point2D&> texture = math::functions::worley_noise2d();

	return std::make_shared<SimpleMaterial2D>(texture >> color_mapper);
}
