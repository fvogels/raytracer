#include "math/functions/worley.h"
#include "math/functions/random-function.h"
#include "math/functions/voronoi.h"
#include <assert.h>
#include <algorithm>
#include <limits>

using namespace math;
using namespace math::functions;


namespace
{
    class WorleyNoise2D : public FunctionBody<double, const Point2D&>
    {
    public:
        WorleyNoise2D(Function<Point2D(const Point2D&)> voronoi)
            : m_voronoi(voronoi)
        {
            // NOP
        }

        double evaluate(const math::Point2D& p) const
        {
            return find_smallest_distance(p);
        }

    private:
        double find_smallest_distance(const Point2D& p) const
        {
            auto closest_point = m_voronoi(p);
            auto dist = distance(p, closest_point);

            return dist;
        }

        Function<Point2D(const Point2D&)> m_voronoi;
    };

    class WorleyNoise3D : public FunctionBody<double, const Point3D&>
    {
    public:
        WorleyNoise3D(Function<Point3D(const Point3D&)> voronoi)
            : m_voronoi(voronoi)
        {
            // NOP
        }

        double evaluate(const math::Point3D& p) const
        {
            return find_smallest_distance(p);
        }

    private:
        double find_smallest_distance(const Point3D& p) const
        {
            return distance(p, m_voronoi(p));
        }

        Function<Point3D(const Point3D&)> m_voronoi;
    };
}

Noise2D math::functions::worley2d(unsigned density, unsigned seed)
{
    return Noise2D(std::make_shared<WorleyNoise2D>(voronoi2d(density, seed)));
}

Noise3D math::functions::worley3d(unsigned density, unsigned seed)
{
    return Noise3D(std::make_shared<WorleyNoise3D>(voronoi3d(density, seed)));
}
