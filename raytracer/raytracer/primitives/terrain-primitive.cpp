#include "primitives/terrain-primitive.h"
#include "primitives/primitives.h"
#include "math/misc.h"
#include "math/interval.h"
#include "math/functions.h"
#include "easylogging++.h"
#include "data-structures/grid.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;

namespace
{
    class PerlinTerrainGenerator
    {
    public:
        PerlinTerrainGenerator(Function<double(const Point2D&)> noise, unsigned squares_along_x, unsigned squares_along_z, double square_x_size, double square_z_size)
            : m_height_map(squares_along_x, squares_along_z), m_normal_map(squares_along_x, squares_along_z), m_square_x_size(square_x_size), m_square_z_size(square_z_size)
        {
            compute_maps(noise, squares_along_x, squares_along_z, square_x_size, square_z_size);
            m_primitive = create_primitive();
        }

        Primitive result() const
        {
            return m_primitive;
        }

    private:
        Primitive create_primitive()
        {
            std::vector<Primitive> triangles;

            for (unsigned x = 0; x < m_height_map.width() - 1; ++x)
            {
                for (unsigned z = 0; z < m_height_map.height() - 1; ++z)
                {
                    Point3D lower_left = vertex_at(x, z);
                    Point3D lower_right = vertex_at(x + 1, z);
                    Point3D upper_left = vertex_at(x, z + 1);
                    Point3D upper_right = vertex_at(x + 1, z + 1);

                    Vector3D lower_left_n = normal_at(x, z);
                    Vector3D lower_right_n = normal_at(x + 1, z);
                    Vector3D upper_left_n = normal_at(x, z + 1);
                    Vector3D upper_right_n = normal_at(x + 1, z + 1);

                    Primitive triangle1 = smooth_triangle(lower_left, upper_right, lower_right, lower_left_n, upper_right_n, lower_right_n);
                    Primitive triangle2 = smooth_triangle(lower_left, upper_left, upper_right, lower_left_n, upper_left_n, upper_right_n);

                    triangles.push_back(triangle1);
                    triangles.push_back(triangle2);
                }
            }

            return accelerated_mesh(triangles);
        }

        void compute_maps(Function<double(const Point2D&)> noise, unsigned squares_along_x, unsigned squares_along_z, double square_x_size, double square_z_size)
        {
            for (unsigned x = 0; x != squares_along_x; ++x)
            {
                for (unsigned z = 0; z != squares_along_z; ++z)
                {
                    const Point2D p(x * square_x_size, z * square_z_size);

                    const double y = noise(p);
                    const double dx = square_x_size;
                    const double dz = square_z_size;
                    const double dydx = (noise(p + Vector2D(dx, 0)) - noise(p - Vector2D(dx, 0))) / (2 * dx);
                    const double dydz = (noise(p + Vector2D(0, dz)) - noise(p - Vector2D(0, dz))) / (2 * dz);
                    const Vector3D n = Vector3D(-dydx, 1, -dydz).normalized();

                    m_height_map[Position2D(x, z)] = y;
                    m_normal_map[Position2D(x, z)] = n;
                }
            }
        }

        Point3D vertex_at(unsigned x, unsigned z)
        {
            return Point3D(x * m_square_x_size, m_height_map[Position2D(x, z)], z * m_square_z_size);
        }

        Vector3D normal_at(unsigned x, unsigned z)
        {
            return m_normal_map[Position2D(x, z)];
        }

        data::Grid<double> m_height_map;
        data::Grid<Vector3D> m_normal_map;
        double m_square_x_size, m_square_z_size;
        Primitive m_primitive;
    };
}


Primitive raytracer::primitives::terrain()
{
    TIMED_FUNC(timerObj);
    LOG(INFO) << "Building terrain...";

    auto noise1 = math::functions::perlin<double, Point2D>(1, 46874);
    auto noise2 = math::functions::perlin<double, Point2D>(1, 761211);
    auto noise3 = math::functions::perlin<double, Point2D>(1, 67542);

    std::function<double(const Point2D&)> lambda = [=](const Point2D& p) -> double {
        return noise1(p * 0.25) * 5 + noise2(p) * 0.5 + noise3(p * 3.1) * 0.05;
    };

    PerlinTerrainGenerator generator(from_lambda(lambda), 500, 500, 0.05, 0.05);

    return generator.result();
}