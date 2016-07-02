#pragma once

#include "math/interval.h"
#include "math/ray.h"


namespace math
{
    class Box
    {
    public:
        Box(const Interval<double>&, const Interval<double>&, const Interval<double>&);

        double size_x() const;
        double size_y() const;
        double size_z() const;

        bool is_hit_positively_by(const math::Ray&) const;
        bool is_hit_by(const math::Ray&) const;

        Box merge(const Box&) const;
        Box intersect(const Box&) const;

        static Box empty();

    private:
        bool math::Box::hits_xy_face(const Ray&, double, bool) const;
        bool math::Box::hits_xz_face(const Ray&, double, bool) const;
        bool math::Box::hits_yz_face(const Ray&, double, bool) const;

        Interval<double> m_x_interval, m_y_interval, m_z_interval;
    };
}