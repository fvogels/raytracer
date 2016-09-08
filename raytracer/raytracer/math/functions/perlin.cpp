#define _USE_MATH_DEFINES
#include "math/functions/perlin.h"
#include "math/vector.h"
#include "math/functions.h"
#include "math/coordinate-systems.h"
#include "data-structures/position.h"
#include "easylogging++.h"
#include <assert.h>
#include <algorithm>
#include <limits>
#include <cmath>
#include <array>

using namespace math;


namespace
{
    /// <summary>
    /// Converts [-1, 1] to [0, 1].
    /// </summary>
    constexpr double normalize(double t)
    {
        return (t + 1) / 2;
    }

    // Function<double(double)> scale1d(double factor)
    // {
    //     std::function<double(double)> lambda = [factor](double x) -> double {
    //         return x * factor;
    //     };

    //     return from_lambda(lambda);
    // }

    Function<Point2D(const Point2D&)> scale2d(double factor)
    {
        std::function<Point2D(const Point2D&)> lambda = [factor](const Point2D& p) -> Point2D {
            return Point2D(p.x() * factor, p.y() * factor);
        };

        return from_lambda(lambda);
    }

    Function<Point3D(const Point3D&)> scale3d(double factor)
    {
        std::function<Point3D(const Point3D&)> lambda = [factor](const Point3D& p) -> Point3D {
            return Point3D(p.x() * factor, p.y() * factor, p.z() * factor);
        };

        return from_lambda(lambda);
    }

    template<unsigned long N>
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

    template<unsigned long K, unsigned long N>
    struct InterpolationHelper
    {
        static double interpolate(const HyperCube<K>& cube, const std::array<double, N>& coordinates)
        {
            using namespace math::functions::easing;

            static_assert(K <= N, "Invalid index");

            double x = InterpolationHelper<K - 1, N>::interpolate(cube.a, coordinates);
            double y = InterpolationHelper<K - 1, N>::interpolate(cube.b, coordinates);
            double t = coordinates[K - 1];

            auto f = stretch_in_space(math::functions::easing::quadratic_inout(), interval(x, y));
            auto result = f(t);

            return result;
        }
    };

    template<unsigned long N>
    struct InterpolationHelper<0, N>
    {
        static double interpolate(const HyperCube<0>& cube, const std::array<double, N>&)
        {
            return cube.x;
        }
    };

    template<unsigned long K, unsigned long N>
    double interpolate(const HyperCube<K>& cube, const std::array<double, N>& coordinates)
    {
        static_assert(K <= N, "Invalid index");

        return InterpolationHelper<K, N>::interpolate(cube, coordinates);
    }

    using Node = HyperCube<0>;

    template<unsigned long>
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
        PerlinNoise2D(Function<Vector2D(const Position&)> random)
            : m_random(random)
        {
            // NOP
        }

        double evaluate(const math::Point2D& p) const
        {
            double fx = floor(p.x());
            double fy = floor(p.y());

            //double rx = p.x() - fx;
            //double ry = p.y() - fy;

            //double z00 = z<0, 0>(p);
            //double z01 = z<0, 1>(p);
            //double z10 = z<1, 0>(p);
            //double z11 = z<1, 1>(p);

            //return normalize((z00 + z01 + z10 + z11) / 4);

            std::array<double, 2> coordinates = { p.x() - fx, p.y() - fy };
            HyperCube<2> hc2{
                HyperCube<1> { Node{ z<0,0>(p) }, Node{ z<1,0>(p) } },
                HyperCube<1> { Node{ z<0,1>(p) }, Node{ z<1,1>(p) } },
            };

            return normalize(interpolate<2, 2>(hc2, coordinates));
        }

    private:
        template<unsigned X, unsigned Y>
        double z(Point2D p) const
        {
            double fx = bound<X>(p.x());
            double fy = bound<Y>(p.y());
            Point2D fp(fx, fy);

            unsigned kx = unsigned(fx);
            unsigned ky = unsigned(fy);

            Vector2D v = m_random(Position(kx, ky));

            return (p - fp).dot(v);
        }

        Function<Vector2D(const Position&)> m_random;
    };

    class PerlinNoise3D : public FunctionBody<double, const Point3D&>
    {
    public:
        PerlinNoise3D(Function<Vector3D(const Position3D&)> random)
            : m_random(random)
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

            double result = normalize(interpolate(hc, coordinates));

            assert(interval(0.0, 1.0).contains(result));

            return result;
        }

    private:
        template<unsigned X, unsigned Y, unsigned Z>
        Node z(Point3D p) const
        {
            double fx = bound<X>(p.x());
            double fy = bound<Y>(p.y());
            double fz = bound<Z>(p.z());
            Point3D fp = Point3D(fx, fy, fz);

            unsigned kx = unsigned(fx);
            unsigned ky = unsigned(fy);
            unsigned kz = unsigned(fz);

            Vector3D v = m_random(Position3D(kx, ky, kz));

            return Node{ (p - fp).dot(v) };
        }

        Function<Vector3D(const Position3D&)> m_random;
    };

    //class PerlinNoise4D : public FunctionBody<double, const Point3D&>
    //{
    //public:
    //    PerlinNoise4D(Function<unsigned(unsigned)> rng)
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

    //    Function<unsigned(unsigned)> m_rng;
    //};
}

using namespace math;
using namespace math::functions;


Noise1D math::functions::_private_::perlin1d(unsigned seed, unsigned octaves)
{
    auto noise2d = perlin2d(seed, octaves);

    std::function<double(const double&)> lambda = [noise2d](const double& t) {
        return noise2d(Point2D(t, 0));
    };

    return from_lambda(lambda);
}

Noise2D math::functions::_private_::perlin2d(unsigned seed, unsigned octaves)
{
    if (octaves == 0)
    {
        LOG(ERROR) << "At least one octave is required";
        abort();
    }
    else
    {
        auto perlin = Noise2D(std::make_shared<PerlinNoise2D>(math::functions::random::position_to_vector2d(seed)));
        Noise2D total = constant<double, const Point2D&>(0);
        double sum_weights = 0;

        for (unsigned i = 0; i < octaves; ++i)
        {
            double weight = pow(2, -double(i));

            total = total + (scale2d(i + 1) >> perlin) * weight;
            sum_weights += weight;
        }

        return total / sum_weights;
    }
}

Noise3D math::functions::_private_::perlin3d(unsigned seed, unsigned octaves)
{
    auto perlin = Noise3D(std::make_shared<PerlinNoise3D>(math::functions::random::position3d_to_vector3d(seed)));
    Noise3D total = constant<double, const Point3D&>(0);
    double sum_weights = 0;

    for (unsigned i = 0; i < octaves; ++i)
    {
        double weight = pow(2, -double(i));

        total = total + (scale3d(i + 1) >> perlin) * weight;
        sum_weights += weight;
    }

    return total / sum_weights;
}

Function<Vector3D(const Point3D&)> math::functions::_private_::perlin_vector3d(unsigned seed, unsigned octaves)
{
    auto perlin = math::functions::_private_::perlin3d(seed, octaves);

    std::function<Vector3D(const Point3D&)> lambda = [perlin](const Point3D& p) -> Vector3D {
        auto azimuth = Angle::degrees(perlin(p) * 360 * 5);
        auto elevation = Angle::degrees(perlin(p + Vector3D(543, 3294589, 489)) * 180 - 90);

        return Vector3D::spherical(1, azimuth, elevation);
    };

    return from_lambda(lambda);
}
