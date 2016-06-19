#include "materials/materials.h"
#include "math/function.h"
#include "math/functions/checkerboard.h"
#include "math/worley-noise2d.h"
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
	auto bool_mapper = math::functions::BoolMapper<color>(c1, c2);
	auto texture = std::make_shared<math::functions::Checkerboard<math::functions::BoolMapper<color>>>(bool_mapper);

	return std::make_shared<SimpleMaterial2D>(texture);
}

class WorleyMaterial : public math::Function<color, const math::Point2D&>
{
public:
	WorleyMaterial()
		: m_worley(math::create_worley_noise2d())
	{
		//  NOP
	}

	color operator ()(const math::Point2D& p) const
	{
		return m_grayscale((*m_worley)(Point2D(p.x * 5, p.y * 5)) * 2);
	}

private:
	Grayscale m_grayscale;
	std::shared_ptr<math::Noise2D> m_worley;
};

std::shared_ptr<Material> raytracer::materials::worley(const color& c1, const color& c2)
{
	auto worley = std::make_shared<WorleyMaterial>();

	return std::make_shared<SimpleMaterial2D>(worley);
}
