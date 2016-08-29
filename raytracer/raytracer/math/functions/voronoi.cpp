#include "math/functions/voronoi.h"
#include "math/functions/random-function.h"
#include <assert.h>
#include <algorithm>
#include <limits>

using namespace math;
using namespace math::functions;


math::Voronoi2D::Voronoi2D(Function<unsigned(unsigned)> rng, unsigned density)
    : m_rng(rng), m_density(density)
{
    // NOP
}

Point2D math::Voronoi2D::closest_to(const math::Point2D& p) const
{
    auto closest = find_closest(p);

    return closest;
}

Point2D math::Voronoi2D::second_closest_to(const math::Point2D& p) const
{
    auto second_closest = find_second_closest(p);

    return second_closest;
}

void math::Voronoi2D::enumerate_points_in_cell(int x, int y, std::function<void(const Point2D&)> callback) const
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

void math::Voronoi2D::enumerate_points_around(const Point2D& p, std::function<void(const Point2D&)> callback) const
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

Point2D math::Voronoi2D::find_closest(const Point2D& p) const
{
    Point2D closest;
    double closest_distance = std::numeric_limits<double>::infinity();

    enumerate_points_around(p, [&](const Point2D& q)
    {
        double dist = distance(p, q);

        if (dist < closest_distance)
        {
            closest = q;
            closest_distance = dist;
        }
    });

    return closest;
}

Point2D math::Voronoi2D::find_second_closest(const Point2D& p) const
{
    Point2D closest;
    Point2D second_closest;
    double closest_distance = std::numeric_limits<double>::infinity();
    double second_closest_distance = std::numeric_limits<double>::infinity();

    enumerate_points_around(p, [&](const Point2D& q)
    {
        double dist = distance(p, q);

        if (dist < closest_distance)
        {
            second_closest = closest;
            second_closest_distance = closest_distance;

            closest = q;
            closest_distance = dist;
        }
        else if (dist < second_closest_distance)
        {
            second_closest = q;
            second_closest_distance = dist;
        }
    });

    return second_closest;
}

math::Voronoi3D::Voronoi3D(Function<unsigned(unsigned)> rng, unsigned density)
    : m_rng(rng), m_density(density)
{
    // NOP
}

Point3D math::Voronoi3D::closest_to(const math::Point3D& p) const
{
    auto closest = find_closest(p);

    return closest;
}

Point3D math::Voronoi3D::second_closest_to(const math::Point3D& p) const
{
    auto second_closest = find_second_closest(p);

    return second_closest;
}

void math::Voronoi3D::enumerate_points_in_cell(int x, int y, int z, std::function<void(const Point3D&)> callback) const
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

void math::Voronoi3D::enumerate_points_around(const Point3D& p, std::function<void(const Point3D&)> callback) const
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

Point3D math::Voronoi3D::find_closest(const Point3D& p) const
{
    Point3D closest;
    double closest_distance = std::numeric_limits<double>::infinity();

    enumerate_points_around(p, [&closest, &closest_distance, &p](const Point3D& q)
    {
        double dist = distance(p, q);

        if (dist < closest_distance)
        {
            closest = q;
            closest_distance = dist;
        }
    });

    return closest;
}

Point3D math::Voronoi3D::find_second_closest(const Point3D& p) const
{
    Point3D closest;
    Point3D second_closest;
    double closest_distance = std::numeric_limits<double>::infinity();
    double second_closest_distance = std::numeric_limits<double>::infinity();

    enumerate_points_around(p, [&](const Point3D& q)
    {
        double dist = distance(p, q);

        if (dist < closest_distance)
        {
            second_closest = closest;
            second_closest_distance = closest_distance;

            closest = q;
            closest_distance = dist;
        }
        else if (dist < second_closest_distance)
        {
            second_closest = q;
            second_closest_distance = dist;
        }
    });

    return second_closest;
}

std::shared_ptr<Voronoi2D> math::voronoi2d(unsigned density, unsigned seed)
{
    return std::make_shared<Voronoi2D>(random_function(seed), density);
}

std::shared_ptr<Voronoi3D> math::voronoi3d(unsigned density, unsigned seed)
{
    return std::make_shared<Voronoi3D>(random_function(seed), density);
}
