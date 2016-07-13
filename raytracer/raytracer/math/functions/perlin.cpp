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

                    unsigned x = unsigned(floor(p.x));
                    unsigned y = unsigned(floor(p.y));

                    double z00 = at(x, y);
                    double z10 = at(x + 1, y);
                    double z01 = at(x, y + 1);
                    double z11 = at(x + 1, y + 1);

                    auto f = easing_function<QUADRATIC, INOUT>(y_range(z00, z10));
                    auto g = easing_function<QUADRATIC, INOUT>(y_range(z01, z11));

                    double z0 = f(p.x - floor(p.x));
                    double z1 = g(p.x - floor(p.x));

                    auto h = easing_function<QUADRATIC, INOUT>(y_range(z0, z1));

                    return h(p.y - floor(p.y));
                }

            private:
                double at(unsigned x, unsigned y) const
                {
                    return double(m_rng(x * 31 + 97 * y)) / std::numeric_limits<unsigned>::max();
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
