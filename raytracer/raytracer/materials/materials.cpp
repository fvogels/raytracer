#include "materials/materials.h"
#include "materials/material2d.h"
#include "materials/uniform-material.h"
#include "math/function.h"
#include "math/functions/functions.h"
#include "math/functions/patterns.h"
#include "math/functions/noise.h"
#include "math/functions/bool-mapper.h"
#include "imaging/color-mapper.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::materials;


std::shared_ptr<Material> raytracer::materials::worley(const color& c1, const color& c2)
{
	auto color_mapper = imaging::color_mapping::grayscale();
	math::Function<double, const Point2D&> texture = math::functions::worley_noise2d();

	return std::make_shared<SimpleMaterial2D>(texture >> color_mapper);
}

std::shared_ptr<Material> raytracer::materials::pattern2d(math::Function<bool, const Point2D&> pattern, const color& c1, const color& c2)
{
	auto bool_mapper = math::functions::bool_mapper(c1, c2);

	return std::make_shared<SimpleMaterial2D>(pattern >> bool_mapper);
}

std::shared_ptr<Material> raytracer::materials::uniform(const color& c)
{
	return std::make_shared<SimpleMaterial2D>(math::functions::constant<color, const Point2D&>(c));
}

std::shared_ptr<Material> raytracer::materials::checkered(const color& c1, const color& c2)
{
	return pattern2d(math::functions::checkered(), c1, c2);
}

std::shared_ptr<Material> raytracer::materials::horizontal_lines(double thickness, const color& c1, const color& c2)
{
	return pattern2d(math::functions::horizontal_lines(thickness), c1, c2);
}

std::shared_ptr<Material> raytracer::materials::vertical_lines(double thickness, const color& c1, const color& c2)
{
	return pattern2d(math::functions::vertical_lines(thickness), c1, c2);
}

std::shared_ptr<Material> raytracer::materials::grid(double thickness, const color& c1, const color& c2)
{
	return pattern2d(math::functions::grid(thickness), c1, c2);
}
