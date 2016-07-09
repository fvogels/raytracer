#include "cameras/orthographic-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::cameras;
using namespace math;


raytracer::cameras::_private_::OrthographicCamera::OrthographicCamera(const math::Matrix4D& transformation, double window_width, double window_height)
    : DisplacableCamera(transformation), m_eye_window(Point3D(window_width / 2, -window_height / 2, 0), Vector3D(-window_width, 0, 0), Vector3D(0, window_height, 0))
{
    // NOP
}

Ray raytracer::cameras::_private_::OrthographicCamera::create_untransformed_ray(const Point2D& point) const
{
    assert(0 <= point.x && point.x <= 1);
    assert(0 <= point.y && point.y <= 1);

    Point3D from = m_eye_window.project(point);

    return Ray(from, Vector3D(0, 0, 1));
}

Camera raytracer::cameras::orthographic(
    const math::Point3D& eye,
    const math::Point3D& look_at,
    const math::Vector3D& up,
    double window_width,
    double aspect_ratio)
{
    assert(up.is_unit());

    double window_height = window_width / aspect_ratio;
    Matrix4D transformation = _private_::create_transformation(eye, look_at, up);

    return Camera(std::make_shared<_private_::OrthographicCamera>(transformation, window_width, window_height));
}