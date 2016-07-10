#include "cameras/depth-of-field-perspective-camera.h"
#include "cameras/perspective-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::cameras;
using namespace math;


raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::DepthOfFieldPerspectiveCamera(const math::Matrix4D transformation, const math::Point3D& look_at, double distance, double aspect_ratio)
    : DisplaceableCamera(transformation), m_look_at(look_at), m_distance(distance), m_aspect_ratio(aspect_ratio)
{
    // NOP
}

void raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::enumerate_untransformed_rays(const Point2D& point, std::function<void(const math::Ray&)> callback) const
{
    assert(0 <= point.x && point.x <= 1);
    assert(0 <= point.y && point.y <= 1);

    Angle delta = 360_degrees / 6;
    const double radius = 0.1;
    for (Angle a = 0_degrees; a < 360_degrees; a += delta)
    {
        Point3D eye(radius * cos(a), radius * sin(a), 0);
        auto camera = perspective(eye, m_look_at, Vector3D(0, 1, 0), m_distance, m_aspect_ratio);

        camera->enumerate_rays(point, callback);
    }
}

Camera raytracer::cameras::depth_of_field_perspective(
    const math::Point3D& eye,
    const math::Point3D& look_at,
    const math::Vector3D& up,
    double distance,
    double aspect_ratio)
{
    assert(up.is_unit());

    Matrix4D transformation = _private_::create_transformation(eye, look_at, up);
    Point3D relative_look_at(0, 0, math::distance(eye, look_at));

    return Camera(std::make_shared<_private_::DepthOfFieldPerspectiveCamera>(transformation, relative_look_at, distance, aspect_ratio));
}