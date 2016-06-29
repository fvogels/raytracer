#include "cameras/fisheye-camera.h"
#include "math/rectangle3d.h"
#include "math/angle.h"
#include "math/interval.h"
#include "math/interval-mapper.h"
#include <assert.h>

using namespace raytracer;
using namespace math;


raytracer::cameras::_private_::FisheyeCamera::FisheyeCamera(const math::Matrix4D& transformation, math::Angle horizontal_view_angle, math::Angle vertical_view_angle)
    : DisplacableCamera(transformation), m_horizontal_view_angle(horizontal_view_angle), m_vertical_view_angle(vertical_view_angle)
{
    // NOP
}

Ray raytracer::cameras::_private_::FisheyeCamera::create_untransformed_ray(const Point2D& point) const
{
    assert(0 <= point.x && point.x <= 1);
    assert(0 <= point.y && point.y <= 1);

    Point3D eye(0, 0, 0);

    Interval<double> x_interval(0, 1);
    Interval<Angle> azimuth_interval(90_degrees - m_horizontal_view_angle / 2, 90_degrees + m_horizontal_view_angle / 2);
    IntervalMapper<double, Angle> azimuth_mapper(x_interval, azimuth_interval);
    Angle azimuth = azimuth_mapper[point.x];

    Interval<double> y_interval(0, 1);
    Interval<Angle> altitude_interval(-m_vertical_view_angle / 2, m_vertical_view_angle / 2);
    IntervalMapper<double, Angle> altitude_mapper(y_interval, altitude_interval);
    Angle altitude = altitude_mapper[point.y];
    
    Point3D through(1.0, azimuth, altitude);

    return Ray(eye, through);
}

std::shared_ptr<cameras::Camera> raytracer::cameras::fisheye(
    const math::Point3D& eye,
    const math::Point3D& look_at,
    const math::Vector3D& up,
    const math::Angle& horizontal_angle,
    const math::Angle& vertical_angle)
{
    assert(up.is_unit());

    Matrix4D transformation = _private_::create_transformation(eye, look_at, up);

    return std::make_shared<_private_::FisheyeCamera>(transformation, horizontal_angle, vertical_angle);
}