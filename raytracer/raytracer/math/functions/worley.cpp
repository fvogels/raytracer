#include "math/functions/worley.h"
#include "math/functions/random-function.h"
#include <assert.h>
#include <algorithm>
#include <limits>


namespace math
{
    namespace functions
    {
        namespace _private_
        {
            class WorleyNoise2D : public FunctionBody<double, const Point2D&>
            {
            public:
                WorleyNoise2D(Function<unsigned(unsigned)> rng)
                    : m_rng(rng)
                {
                    // NOP
                }

                double evaluate(const math::Point2D& p) const
                {
                    return find_smallest_distance(p);
                }

            private:
                void enumerate_points_in_cell(int x, int y, std::function<void(const Point2D&)> callback) const
                {
                    for (int i = 0; i != 10; ++i)
                    {
                        unsigned k = x * 71767 + y * 19178 + i * 57465;

                        double fx = double(m_rng(k)) / std::numeric_limits<unsigned>::max();
                        double fy = double(m_rng(k + 1)) / std::numeric_limits<unsigned>::max();
                        Point2D p = point(x + fx, y + fy);

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

                double find_smallest_distance(const Point2D& p) const
                {
                    double closest = sqrt(2);

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

                Function<unsigned(unsigned)> m_rng;
            };

            class WorleyNoise3D : public FunctionBody<double, const Point3D&>
            {
            public:
                WorleyNoise3D(Function<unsigned(unsigned)> rng)
                    : m_rng(rng)
                {
                    // NOP
                }

                double evaluate(const math::Point3D& p) const
                {
                    return find_smallest_distance(p);
                }

            private:
                void enumerate_points_in_cell(int x, int y, int z, std::function<void(const Point3D&)> callback) const
                {
                    for (int i = 0; i != 10; ++i)
                    {
                        unsigned k = x * 71767 + y * 9178 + z * 73467 + i * 57465;

                        double fx = double(m_rng(k)) / std::numeric_limits<unsigned>::max();
                        double fy = double(m_rng(k + 1)) / std::numeric_limits<unsigned>::max();
                        double fz = double(m_rng(k + 2)) / std::numeric_limits<unsigned>::max();
                        Point3D p = Point3D(x + fx, y + fy, z + fz);

                        callback(p);
                    }
                }

                void enumerate_points_around(const Point3D& p, std::function<void(const Point3D&)> callback) const
                {
                    int x = int(floor(p.x()));
                    int y = int(floor(p.y()));
                    int z = int(floor(p.z()));

                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        for (int dy = -1; dy <= 1; ++dy)
                        {
                            for (int dz = -1; dz <= 1; ++dz)
                            {
                                enumerate_points_in_cell(x + dx, y + dy, z + dz, callback);
                            }
                        }
                    }
                }

                double find_smallest_distance(const Point3D& p) const
                {
                    double closest = sqrt(3);

                    enumerate_points_around(p, [&closest, &p](const Point3D& q)
                    {
                        closest = std::min(closest, distance(p, q));
                    });

                    double result = closest;

                    result = std::min(result, 1.0);

                    assert(0 <= result);
                    assert(result <= 1);

                    return result;
                }

                Function<unsigned(unsigned)> m_rng;
            };
        }
    }
}

using namespace math;
using namespace math::functions;

Noise2D math::functions::worley2d(unsigned seed)
{
    return Noise2D(std::make_shared<_private_::WorleyNoise2D>(random_function(seed)));
}

Noise3D math::functions::worley3d(unsigned seed)
{
    return Noise3D(std::make_shared<_private_::WorleyNoise3D>(random_function(seed)));
}
