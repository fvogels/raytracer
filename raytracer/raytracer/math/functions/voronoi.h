#pragma once

#include "math/function.h"
#include "math/point.h"


namespace math
{
    class Voronoi2D
    {
    public:
        Voronoi2D::Voronoi2D(Function<unsigned(unsigned)> rng, unsigned density);

        Point2D closest_to(const Point2D&) const;
        Point2D second_closest_to(const Point2D&) const;

    private:
        void enumerate_points_in_cell(int x, int y, std::function<void(const Point2D&)> callback) const;
        void enumerate_points_around(const Point2D& p, std::function<void(const Point2D&)> callback) const;
        Point2D find_closest(const Point2D& p) const;
        Point2D find_second_closest(const Point2D& p) const;

        Function<unsigned(unsigned)> m_rng;
        unsigned m_density;
    };

    class Voronoi3D
    {
    public:
        Voronoi3D::Voronoi3D(Function<unsigned(unsigned)> rng, unsigned density);

        Point3D closest_to(const Point3D&) const;
        Point3D second_closest_to(const Point3D&) const;

    private:
        void enumerate_points_in_cell(int x, int y, int z, std::function<void(const Point3D&)> callback) const;
        void enumerate_points_around(const Point3D& p, std::function<void(const Point3D&)> callback) const;
        Point3D find_closest(const Point3D& p) const;
        Point3D find_second_closest(const Point3D& p) const;

        Function<unsigned(unsigned)> m_rng;
        unsigned m_density;
    };

    std::shared_ptr<Voronoi2D> voronoi2d(unsigned density, unsigned seed = 56373);
    std::shared_ptr<Voronoi3D> voronoi3d(unsigned density, unsigned seed = 56373);
}