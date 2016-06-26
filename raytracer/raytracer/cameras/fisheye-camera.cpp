#include "cameras/fisheye-camera.h"
#include "math/rectangle3d.h"
#include "math/angle.h"
#include "math/interval.h"
#include "math/interval-mapper.h"
#include <assert.h>

using namespace raytracer;
using namespace math;


raytracer::cameras::FisheyeCamera::FisheyeCamera(const math::Matrix4D& transformation, math::Angle horizontal_view_angle, math::Angle vertical_view_angle)
    : DisplacableCamera(transformation), m_horizontal_view_angle(horizontal_view_angle), m_vertical_view_angle(vertical_view_angle)
{
    // NOP
}

Ray raytracer::cameras::FisheyeCamera::create_untransformed_ray(const Point2D& point) const
{
    assert(0 <= point.x && point.x <= 1);
    assert(0 <= point.y && point.y <= 1);

    Point3D eye(0, 0, 0);

    Interval<double> x_interval(0, 1);
    Interval<Angle> hangle_interval(90_degrees - m_horizontal_view_angle / 2, 90_degrees + m_horizontal_view_angle / 2);
    IntervalMapper<double, Angle> hangle_mapper(x_interval, hangle_interval);
    Angle hangle = hangle_mapper[point.x];

    Interval<double> y_interval(0, 1);
    Interval<Angle> vangle_interval(-m_vertical_view_angle / 2, m_vertical_view_angle / 2);
    IntervalMapper<double, Angle> vangle_mapper(y_interval, vangle_interval);
    Angle vangle = vangle_mapper[point.y];

    double x = cos(vangle) * cos(hangle);
    double y = sin(vangle);
    double z = cos(vangle) * sin(hangle);
    Point3D through(x, y, z);

    return Ray(eye, through);
}