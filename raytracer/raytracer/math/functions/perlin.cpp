#include "math/functions/perlin.h"
#include "math/functions/random-function.h"
#include "math/functions/easing-functions.h"
#include <assert.h>
#include <algorithm>
#include <limits>


namespace math
{
    namespace functions
    {
        namespace _private_
        {
            class PerlinNoise2D : public FunctionBody<double, const Point2D&>
            {
            public:
                PerlinNoise2D(Function<unsigned, unsigned> rng)
                    : m_rng(rng)
                {
                    // NOP
                }

                double evaluate(const math::Point2D& p) const
                {
                    using namespace math::functions::easing;

                    double fx = floor(p.x);
                    double fy = floor(p.y);

                    unsigned x = unsigned(fx);
                    unsigned y = unsigned(fy);

                    Point2D q = Point2D(p.x - fx, p.y - fy);

                    Point2D p00 = Point2D(fx, fy);
                    Point2D p10 = Point2D(fx + 1, fy);
                    Point2D p01 = Point2D(fx, fy + 1);
                    Point2D p11 = Point2D(fx + 1, fy + 1);

                    Vector2D v00 = at(x, y);
                    Vector2D v10 = at(x + 1, y);
                    Vector2D v01 = at(x, y + 1);
                    Vector2D v11 = at(x + 1, y + 1);                    

                    double z00 = (p - p00).dot(v00);
                    double z10 = (p - p10).dot(v10);
                    double z01 = (p - p01).dot(v01);
                    double z11 = (p - p11).dot(v11);

                    auto f = easing_function<QUADRATIC, INOUT>(y_range(z00, z10));
                    auto g = easing_function<QUADRATIC, INOUT>(y_range(z01, z11));

                    double z0 = f(q.x);
                    double z1 = g(q.x);

                    auto h = easing_function<QUADRATIC, INOUT>(y_range(z0, z1));

                    double result = (h(q.y) + 1) / 2;

                    assert(0 <= result);
                    assert(result <= 1);

                    return result;
                }

            private:
                Vector2D at(unsigned x, unsigned y) const
                {
                    auto t = double(m_rng(x * 31 + 97 * y)) / std::numeric_limits<unsigned>::max();

                    return Vector2D(1, t * 360_degrees);
                }

                Function<unsigned, unsigned> m_rng;
            };
        }
    }
}

using namespace math;
using namespace math::functions;

Noise2D math::functions::perlin2d(unsigned seed)
{
    return Noise2D(std::make_shared<_private_::PerlinNoise2D>(random_function(seed)));
}
