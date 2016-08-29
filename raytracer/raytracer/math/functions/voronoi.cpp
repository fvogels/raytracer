#include "math/functions/voronoi.h"
#include "math/functions/random-function.h"
#include <assert.h>
#include <algorithm>
#include <limits>

using namespace math;
using namespace math::functions;


namespace
{
    class Voronoi2D : public FunctionBody<Point2D, const Point2D&>
    {
    public:
        Voronoi2D(Function<unsigned(unsigned)> rng, unsigned density)
            : m_rng(rng), m_density(density)
        {
            // NOP
        }

        Point2D evaluate(const math::Point2D& p) const
        {
            return find_closest(p);
        }

    private:
        void enumerate_points_in_cell(int x, int y, std::function<void(const Point2D&)> callback) const
        {
            for (int i = 0; i != m_density; ++i)
            {
                unsigned k = x * 71767 + y * 19178 + i * 57465;

                double fx = double(m_rng(k)) / std::numeric_limits<unsigned>::max();
                double fy = double(m_rng(k + 1)) / std::numeric_limits<unsigned>::max();
                Point2D p(x + fx, y + fy);

                callback(p);
            }
        }

        void enumerate_points_around(const Point2D& p, std::function<void(const Point2D&)> callback) const
        {
            int x = int(floor(p.x()));
            int y = int(floor(p.y()));

            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    enumerate_points_in_cell(x + dx, y + dy, callback);
                }
            }
        }

        Point2D find_closest(const Point2D& p) const
        {
            Point2D closest;
            double closest_distance = std::numeric_limits<double>::infinity();

            enumerate_points_around(p, [&closest, &closest_distance, &p](const Point2D& q)
            {
                double dist = distance(p, q);

                if (dist < closest_distance)
                {
                    closest = p;
                    closest_distance = dist;
                }
            });

            return closest;
        }

        Function<unsigned(unsigned)> m_rng;
        unsigned m_density;
    };
}

math::Function<math::Point2D(const math::Point2D&)> math::functions::voronoi2d(unsigned seed, unsigned density)
{
    return math::Function<math::Point2D(const math::Point2D&)>(std::make_shared<Voronoi2D>(random_function(seed), density));
}
