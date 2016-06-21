#include "math/functions/worley-noise.h"
#include <algorithm>
#include <functional>
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
		double operator ()(const math::Point2D&) const;

	private:
		void enumerate_points_in_cell(int, int, std::function<void(const Point2D&)>) const;
		void enumerate_points_around(const Point2D&, std::function<void(const Point2D&)>) const;
		double find_smallest_distance(const Point2D&) const;
	};
}

void math::WorleyNoise2D::enumerate_points_in_cell(int x, int y, std::function<void(const Point2D&)> callback) const
{
	srand(x * 579 + y * 764);

	for (int i = 0; i != 10; ++i)
	{
		double fx = double(rand()) / RAND_MAX;
		double fy = double(rand()) / RAND_MAX;
		Point2D p(x + fx, y + fy);

		callback(p);
	}
}

void math::WorleyNoise2D::enumerate_points_around(const Point2D& p, std::function<void(const Point2D&)> callback) const
{
	int x = int(std::floor(p.x));
	int y = int(std::floor(p.y));

	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			enumerate_points_in_cell(x + dx, y + dy, callback);
		}
	}
}

double math::WorleyNoise2D::operator ()(const math::Point2D& p) const
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

	enumerate_points_around(p, [&closest, &p](const Point2D& q)
	{
		closest = std::min(closest, distance(p, q));
	});

	double result = closest;

	result = std::min(result, 1.0);

	assert(0 <= result);
	assert(result <= 1);

	return result;
}

std::shared_ptr<Noise2D> math::create_worley_noise2d()
{
	return std::make_shared<WorleyNoise2D>();
}