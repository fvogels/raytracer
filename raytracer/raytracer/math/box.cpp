#include "math/box.h"
#include "math/ray.h"
#include <limits>

using namespace math;


math::Box::Box(const Interval<double>& x_interval, const Interval<double>& y_interval, const Interval<double>& z_interval)
    : m_x_interval(x_interval), m_y_interval(y_interval), m_z_interval(z_interval)
{
    // NOP
}

bool math::Box::hits(const Ray& ray) const
{
    return
        hits_xy_face(ray, m_x_interval.lower) ||
        hits_xy_face(ray, m_x_interval.upper) ||
        hits_xz_face(ray, m_y_interval.lower) ||
        hits_xz_face(ray, m_y_interval.upper) ||
        hits_yz_face(ray, m_z_interval.lower) ||
        hits_yz_face(ray, m_z_interval.upper);
}

bool math::Box::hits_xy_face(const Ray& ray, double z) const
{
    if (ray.direction.z == approx(0.0))
    {
        return false;
    }
    else
    {
        double t = -(ray.origin.z - z) / ray.direction.z;
        Point3D p = ray.at(t);

        return t > 0 && m_x_interval.contains(p.x) && m_y_interval.contains(p.y);
    }
}

bool math::Box::hits_xz_face(const Ray& ray, double y) const
{
    if (ray.direction.y == approx(0.0))
    {
        return false;
    }
    else
    {
        double t = -(ray.origin.y - y) / ray.direction.y;
        Point3D p = ray.at(t);

        return t > 0 && m_x_interval.contains(p.x) && m_z_interval.contains(p.z);
    }
}

bool math::Box::hits_yz_face(const Ray& ray, double x) const
{
    if (ray.direction.x == approx(0.0))
    {
        return false;
    }
    else
    {
        double t = -(ray.origin.x - x) / ray.direction.x;
        Point3D p = ray.at(t);

        return t > 0 && m_y_interval.contains(p.y) && m_z_interval.contains(p.z);
    }
}

Box math::Box::empty()
{
    Interval<double> interval = Interval<double>::empty();

    return Box(interval, interval, interval);
}

Box math::Box::merge(const Box& other) const
{
    return Box(m_x_interval.merge(other.m_x_interval), m_y_interval.merge(other.m_y_interval), m_z_interval.merge(other.m_z_interval));
}

Box math::Box::intersect(const Box& other) const
{
    return Box(m_x_interval.intersect(other.m_x_interval), m_y_interval.intersect(other.m_y_interval), m_z_interval.intersect(other.m_z_interval));
}