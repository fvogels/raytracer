#define _USE_MATH_DEFINES
#include "math/functions/perlin.h"
#include "math/vector2d.h"
#include "math/functions/random-function.h"
#include "math/functions/easing-functions.h"
#include <assert.h>
#include <algorithm>
#include <limits>
#include <math.h>
#include <array>


namespace math
{
    namespace functions
    {
        namespace _private_
        {
            Function<Point2D, const Point2D&> scale2d(double factor)
            {
                std::function<Point2D(const Point2D&)> lambda = [factor](const Point2D& p) -> Point2D {
                    return point(p.x() * factor, p.y() * factor);
                };

                return from_lambda(lambda);
            }

            Function<Point3D, const Point3D&> scale3d(double factor)
            {
                std::function<Point3D(const Point3D&)> lambda = [factor](const Point3D& p) -> Point3D {
                    return point(p.x() * factor, p.y() * factor, p.z() * factor);
                };

                return from_lambda(lambda);
            }

            template<unsigned N>
            struct HyperCube
            {
                HyperCube<N - 1> a;
                HyperCube<N - 1> b;
            };

            template<>
            struct HyperCube<0>
            {
                double x;
            };

            template<unsigned K, unsigned N>
            struct InterpolationHelper
            {
                static double interpolate(const HyperCube<K>& cube, const std::array<double, N>& coordinates)
                {
                    using namespace math::functions::easing;

                    static_assert(K <= N, "Invalid index");

                    double x = InterpolationHelper<K - 1, N>::interpolate(cube.a, coordinates);
                    double y = InterpolationHelper<K - 1, N>::interpolate(cube.b, coordinates);
                    double t = coordinates[K - 1];

                    auto f = easing_function<QUADRATIC, INOUT>(y_range(x, y));
                    auto result = f(t);

                    return result;
                }
            };

            template<unsigned N>
            struct InterpolationHelper<0, N>
            {
                static double interpolate(const HyperCube<0>& cube, const std::array<double, N>& coordinates)
                {
                    return cube.x;
                }
            };

            template<unsigned K, unsigned N>
            double interpolate(const HyperCube<K>& cube, const std::array<double, N>& coordinates)
            {
                static_assert(K <= N, "Invalid index");

                return InterpolationHelper<K, N>::interpolate(cube, coordinates);
            }

            using Node = HyperCube<0>;

            template<unsigned>
            double bound(double);

            template<>
            double bound<0>(double x)
            {
                return floor(x);
            }

            template<>
            double bound<1>(double x)
            {
                return ceil(x);
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
                    double fx = floor(p.x());
                    double fy = floor(p.y());

                    std::array<double, 2> coordinates = { p.x() - fx, p.y() - fy };

                    HyperCube<2> hc2{
                        HyperCube<1> { Node{ z<0,0>(p) }, Node{ z<1,0>(p) } },
                        HyperCube<1> { Node{ z<0,1>(p) }, Node{ z<1,1>(p) } },
                    };

                    return interpolate(hc2, coordinates);
                }

            private:
                Vector2D gradient_at(unsigned x, unsigned y) const
                {
                    auto t = double(m_rng(x * 31 + 97 * y)) / std::numeric_limits<unsigned>::max();

                    return vector(1.0, t * 360_degrees);
                }

                template<unsigned X, unsigned Y>
                double z(Point2D p) const
                {
                    double fx = bound<X>(p.x());
                    double fy = bound<Y>(p.y());
                    Point2D fp = point(fx, fy);

                    unsigned kx = unsigned(fx);
                    unsigned ky = unsigned(fy);

                    Vector2D v = gradient_at(kx, ky);

                    return (p - fp).dot(v);
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
                    double fx = floor(p.x());
                    double fy = floor(p.y());
                    double fz = floor(p.z());

                    std::array<double, 3> coordinates = { p.x() - fx, p.y() - fy, p.z() - fz };

                    HyperCube<3> hc
                    {
                        HyperCube<2> {
                            HyperCube<1> { z<0,0,0>(p), z<1,0,0>(p) },
                            HyperCube<1> { z<0,1,0>(p), z<1,1,0>(p) }
                        },
                        HyperCube<2> {
                            HyperCube<1> { z<0,0,1>(p), z<1,0,1>(p) },
                            HyperCube<1> { z<0,1,1>(p), z<1,1,1>(p) }
                        }
                    };

                    return interpolate(hc, coordinates);
                }

            private:
                Vector3D gradient_at(unsigned x, unsigned y, unsigned z) const
                {
                    auto t1 = double(m_rng(x * 31 + 97 * y + 113 * z)) / std::numeric_limits<unsigned>::max();
                    auto t2 = double(m_rng(x * 31 + 97 * y + 113 * z) + 1) / std::numeric_limits<unsigned>::max();

                    return vector(1, t1 * 360_degrees, t2 * 180_degrees);
                }

                template<unsigned X, unsigned Y, unsigned Z>
                Node z(Point3D p) const
                {
                    double fx = bound<X>(p.x());
                    double fy = bound<Y>(p.y());
                    double fz = bound<Z>(p.z());
                    Point3D fp = point(fx, fy, fz);

                    unsigned kx = unsigned(fx);
                    unsigned ky = unsigned(fy);
                    unsigned kz = unsigned(fz);

                    Vector3D v = gradient_at(kx, ky, kz);

                    return Node{ (p - fp).dot(v) };
                }

                Function<unsigned, unsigned> m_rng;
            };

            //class PerlinNoise4D : public FunctionBody<double, const Point3D&>
            //{
            //public:
            //    PerlinNoise4D(Function<unsigned, unsigned> rng)
            //        : m_rng(rng)
            //    {
            //        // NOP
            //    }

            //    double evaluate(const math::Point4D& p) const
            //    {
            //        double fx = floor(p.x);
            //        double fy = floor(p.y);
            //        double fz = floor(p.z);

            //        std::array<double, 3> coordinates = { p.x - fx, p.y - fy, p.z - fz };

            //        HyperCube<3> hc
            //        {
            //            HyperCube<2> {
            //            HyperCube<1> { z<0,0,0>(p), z<1,0,0>(p) },
            //                HyperCube<1> { z<0,1,0>(p), z<1,1,0>(p) }
            //        },
            //            HyperCube<2> {
            //            HyperCube<1> { z<0,0,1>(p), z<1,0,1>(p) },
            //                HyperCube<1> { z<0,1,1>(p), z<1,1,1>(p) }
            //        }
            //        };

            //        return interpolate(hc, coordinates);
            //    }

            //private:
            //    Vector3D gradient_at(unsigned x, unsigned y, unsigned z) const
            //    {
            //        auto t1 = double(m_rng(x * 31 + 97 * y + 113 * z)) / std::numeric_limits<unsigned>::max();
            //        auto t2 = double(m_rng(x * 31 + 97 * y + 113 * z) + 1) / std::numeric_limits<unsigned>::max();

            //        return Vector3D(1, t1 * 360_degrees, t2 * 180_degrees);
            //    }

            //    template<unsigned X, unsigned Y, unsigned Z>
            //    Node z(Point3D p) const
            //    {
            //        double fx = bound<X>(p.x);
            //        double fy = bound<Y>(p.y);
            //        double fz = bound<Z>(p.z);
            //        Point3D fp(fx, fy, fz);

            //        unsigned kx = unsigned(fx);
            //        unsigned ky = unsigned(fy);
            //        unsigned kz = unsigned(fz);

            //        Vector3D v = gradient_at(kx, ky, kz);

            //        return Node{ (p - fp).dot(v) };
            //    }

            //    Function<unsigned, unsigned> m_rng;
            //};
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
        total = total + (_private_::scale2d(i) >> p) / double(i);
    }

    std::function<double(const Point2D&)> lambda = [total, turbulence](const Point2D& p) -> double {
        double t = p.x() + p.y();
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
        double t = p.x() + p.y();
        return abs(sin(360_degrees * t + 360_degrees * turbulence * total(p)));
    };

    return from_lambda<double, const Point3D&>(lambda);
}

Noise2D math::functions::wood2d(unsigned octaves, double turbulence)
{
    auto p = perlin2d(15);

    Noise2D total = p;

    for (unsigned i = 2; i <= octaves; ++i)
    {
        total = total + (_private_::scale2d(i) >> p) / double(i);
    }

    std::function<double(const Point2D&)> lambda = [total, turbulence](const Point2D& p) -> double {
        double t = sqrt(p.x() * p.x() + p.y() * p.y());
        return abs(sin(360_degrees * t + 360_degrees * turbulence * total(p)));
    };

    return from_lambda<double, const Point2D&>(lambda);
}