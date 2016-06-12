#include "math/worley-noise2d.h"
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <limits>

using namespace math;


namespace math
{
	class WorleyNoise2D : public Noise2D
	{
	public:
		WorleyNoise2D(unsigned);

		double operator [](const math::Point2D&) const override;

	private:
		std::vector<Point2D> m_points;

		double find_smallest_distance(const Point2D&) const;
	};
}

math::WorleyNoise2D::WorleyNoise2D(unsigned density)
{
	for (unsigned i = 0; i < density; ++i)
	{
		double x = double(rand()) / RAND_MAX;
		double y = double(rand()) / RAND_MAX;

		m_points.push_back(Point2D(x, y));
	}
}

double math::WorleyNoise2D::operator [](const math::Point2D& p) const
{
	assert(0 <= p.x);
	assert(p.x <= 1);
	assert(0 <= p.y);
	assert(p.y <= 1);

	return find_smallest_distance(p);
}

double math::WorleyNoise2D::find_smallest_distance(const Point2D& p) const
{
	double closest = std::sqrt(2);

	for (auto& q : m_points)
	{
		closest = std::min(closest, distance(p, q));
	}

	double result = closest / std::sqrt(2);

	assert(0 <= result);
	assert(result <= 1);

	return result;
}

std::shared_ptr<Noise2D> math::create_worley_noise2d(unsigned density)
{
	return std::make_shared<WorleyNoise2D>(density);
}