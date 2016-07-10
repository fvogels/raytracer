#include "cameras/depth-of-field-perspective-camera.h"
#include "cameras/perspective-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::cameras;
using namespace raytracer::samplers;
using namespace math;


raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::DepthOfFieldPerspectiveCamera(
    const math::Matrix4D transformation, 
    const math::Point3D& look_at, 
    double distance,
    double aspect_ratio,
    double eye_size,
    Sampler eye_sampler)
    : DisplaceableCamera(transformation)
    , m_look_at(look_at)
    , m_distance(distance)
    , m_aspect_ratio(aspect_ratio)
    , m_eye_window(Rectangle2D(Point2D(-eye_size / 2, -eye_size / 2), Vector2D(eye_size, 0), Vector2D(0, eye_size)))
    , m_eye_sampler(eye_sampler)
{
    // NOP
}

void raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::enumerate_untransformed_rays(const Point2D& point, std::function<void(const math::Ray&)> callback) const
{
    assert(0 <= point.x && point.x <= 1);
    assert(0 <= point.y && point.y <= 1);

    m_eye_sampler->sample(m_eye_window, [this, &point, &callback](const Point2D& eye) {
        auto camera = perspective(Point3D(eye.x, eye.y, 0), m_look_at, Vector3D(0, 1, 0), m_distance, m_aspect_ratio);

        camera->enumerate_rays(point, callback);
    });
}

Camera raytracer::cameras::depth_of_field_perspective(
    const math::Point3D& eye,
    const math::Point3D& look_at,
    const math::Vector3D& up,
    double distance,
    double aspect_ratio,
    double eye_size,
    raytracer::samplers::Sampler eye_sampler)
{
    assert(up.is_unit());

    Matrix4D transformation = _private_::create_transformation(eye, look_at, up);
    Point3D relative_look_at(0, 0, math::distance(eye, look_at));

    return Camera(std::make_shared<_private_::DepthOfFieldPerspectiveCamera>(transformation, relative_look_at, distance, aspect_ratio, eye_size, eye_sampler));
}