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
        virtual Point3D closest_to(const Point3D&) const = 0;
        virtual Point3D second_closest_to(const Point3D&) const = 0;
    };

    std::shared_ptr<Voronoi2D> voronoi2d(unsigned density, unsigned seed = 56373);
    std::shared_ptr<Voronoi3D> voronoi3d(unsigned density, unsigned seed = 56373);
}