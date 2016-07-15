#define _USE_MATH_DEFINES
#include "math/functions/perlin.h"
#include "math/functions/random-function.h"
#include "math/functions/easing-functions.h"
#include <assert.h>
#include <algorithm>
#include <limits>
#include <math.h>


namespace math
{
    namespace functions
    {
        namespace _private_
        {
            Function<Point2D, const Point2D&> scale(double factor)
            {
                std::function<Point2D(const Point2D&)> lambda = [factor](const Point2D& p) -> Point2D {
                    return Point2D(p.x * factor, p.y * factor);
                };

                return from_lambda(lambda);
            }

            Function<Point3D, const Point3D&> scale3d(double factor)
            {
                std::function<Point3D(const Point3D&)> lambda = [factor](const Point3D& p) -> Point3D {
                    return Point3D(p.x * factor, p.y * factor, p.z * factor);
                };

                return from_lambda(lambda);
            }

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

            class PerlinNoise3D : public FunctionBody<double, const Point3D&>
            {
            public:
                PerlinNoise3D(Function<unsigned, unsigned> rng)
                    : m_rng(rng)
                {
                    // NOP
                }

                double evaluate(const math::Point3D& p) const
                {
                    using namespace math::functions::easing;

                    double fx = floor(p.x);
                    double fy = floor(p.y);
                    double fz = floor(p.z);

                    unsigned x = unsigned(fx);
                    unsigned y = unsigned(fy);
                    unsigned z = unsigned(fz);

                    Point3D q = Point3D(p.x - fx, p.y - fy, p.z - fz);

                    Point3D p000 = Point3D(fx, fy, fz);
                    Point3D p100 = Point3D(fx + 1, fy, fz);
                    Point3D p010 = Point3D(fx, fy + 1, fz);
                    Point3D p110 = Point3D(fx + 1, fy + 1, fz);
                    Point3D p001 = Point3D(fx, fy, fz + 1);
                    Point3D p101 = Point3D(fx + 1, fy, fz + 1);
                    Point3D p011 = Point3D(fx, fy + 1, fz + 1);
                    Point3D p111 = Point3D(fx + 1, fy + 1, fz + 1);

                    Vector3D v000 = at(x, y, z);
                    Vector3D v100 = at(x + 1, y, z);
                    Vector3D v010 = at(x, y + 1, z);
                    Vector3D v110 = at(x + 1, y + 1, z);
                    Vector3D v001 = at(x, y, z + 1);
                    Vector3D v101 = at(x + 1, y, z + 1);
                    Vector3D v011 = at(x, y + 1, z + 1);
                    Vector3D v111 = at(x + 1, y + 1, z + 1);

                    double z000 = (p - p000).dot(v000);
                    double z100 = (p - p100).dot(v100);
                    double z010 = (p - p010).dot(v010);
                    double z110 = (p - p110).dot(v110);
                    double z001 = (p - p001).dot(v001);
                    double z101 = (p - p101).dot(v101);
                    double z011 = (p - p011).dot(v011);
                    double z111 = (p - p111).dot(v111);

                    auto f1 = easing_function<QUADRATIC, INOUT>(y_range(z000, z100));
                    auto f2 = easing_function<QUADRATIC, INOUT>(y_range(z010, z110));
                    auto f3 = easing_function<QUADRATIC, INOUT>(y_range(z001, z101));
                    auto f4 = easing_function<QUADRATIC, INOUT>(y_range(z011, z111));

                    double z0 = f1(q.x);
                    double z1 = f2(q.x);
                    double z2 = f3(q.x);
                    double z3 = f4(q.x);

                    auto g1 = easing_function<QUADRATIC, INOUT>(y_range(z0, z1));
                    auto g2 = easing_function<QUADRATIC, INOUT>(y_range(z2, z3));

                    double w0 = g1(q.y);
                    double w1 = g2(q.y);

                    auto h = easing_function<QUADRATIC, INOUT>(y_range(w0, w1));

                    double result = (h(q.z) + 1) / 2;

                    assert(0 <= result);
                    assert(result <= 1);

                    return result;
                }

            private:
                Vector3D at(unsigned x, unsigned y, unsigned z) const
                {
                    auto t1 = double(m_rng(x * 31 + 97 * y + 113 * z)) / std::numeric_limits<unsigned>::max();
                    auto t2 = double(m_rng(x * 31 + 97 * y + 113 * z) + 1) / std::numeric_limits<unsigned>::max();

                    return Vector3D(1, t1 * 360_degrees, t2 * 180_degrees);
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

Noise3D math::functions::perlin3d(unsigned seed)
{
    return Noise3D(std::make_shared<_private_::PerlinNoise3D>(random_function(seed)));
}


Noise2D math::functions::marble2d(unsigned octaves, double turbulence)
{
    auto p = perlin2d(15);

    Noise2D total = p;

    for (unsigned i = 2; i <= octaves; ++i)
    {
        total = total + (_private_::scale(i) >> p) / double(i);
    }

    std::function<double(const Point2D&)> lambda = [total, turbulence](const Point2D& p) -> double {
        double t = p.x + p.y;
        return abs(sin(360_degrees * t + 360_degrees * turbulence * total(p)));
    };

    return from_lambda<double, const Point2D&>(lambda);
}

Noise3D math::functions::marble3d(unsigned octaves, double turbulence)
{
    auto p = perlin3d(71);

    Noise3D total = p;

    for (unsigned i = 2; i <= octaves; ++i)
    {
        total = total + (_private_::scale3d(i) >> p) / double(i);
    }

    std::function<double(const Point3D&)> lambda = [total, turbulence](const Point3D& p) -> double {
        double t = p.x + p.y;
        return abs(sin(360_degrees * t + 360_degrees * turbulence * total(p)));
    };

    return from_lambda<double, const Point3D&>(lambda);
}