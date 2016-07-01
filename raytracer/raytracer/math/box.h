#pragma once

#include "math/interval.h"


namespace math
{
    class Box
    {
    public:
        Box(const Interval<double>&, const Interval<double>&, const Interval<double>&);

        bool hits(const Ray&) const;

    private:
        bool math::Box::hits_xy_face(const Ray&, double) const;
        bool math::Box::hits_xz_face(const Ray&, double) const;
        bool math::Box::hits_yz_face(const Ray&, double) const;

        Interval<double> m_x_interval, m_y_interval, m_z_interval;
    };
}