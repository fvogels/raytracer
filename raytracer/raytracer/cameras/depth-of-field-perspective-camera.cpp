#include "cameras/depth-of-field-perspective-camera.h"
#include "cameras/perspective-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::cameras;
using namespace raytracer::samplers;
using namespace math;


raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::DepthOfFieldPerspectiveCamera(const math::Matrix4D transformation, const std::vector<Camera>& cameras)
    : DisplaceableCamera(transformation), m_cameras(cameras)
{
    // NOP
}

void raytracer::cameras::_private_::DepthOfFieldPerspectiveCamera::enumerate_untransformed_rays(const Point2D& point, std::function<void(const math::Ray&)> callback) const
{
    assert(0 <= point.x() && point.x() <= 1);
    assert(0 <= point.y() && point.y() <= 1);

    for (auto& camera : m_cameras)
    {
        camera->enumerate_rays(point, callback);
    }
}

Camera raytracer::cameras::depth_of_field_perspective(
    const math::Point3D& eye,
    const math::Point3D& look_at,
    const math::Vector3D& up,
    double distance,
    double aspect_ratio,
    double eye_size,
    raytracer::Sampler eye_sampler)
{
    assert(up.is_unit());

    Matrix4D transformation = _private_::create_transformation(eye, look_at, up);
    Point3D relative_look_at = point(0, 0, math::distance(eye, look_at));

    std::vector<Camera> cameras;
    Rectangle2D eye_window(point(-eye_size / 2, -eye_size / 2), vector(eye_size, 0), vector(0, eye_size));
    eye_sampler->sample(eye_window, [&cameras, &relative_look_at, distance, aspect_ratio](Point2D eye) {
        cameras.push_back(perspective(point(eye.x(), eye.y(), 0), relative_look_at, vector(0, 1, 0), distance, aspect_ratio));
    });

    return Camera(std::make_shared<_private_::DepthOfFieldPerspectiveCamera>(transformation, cameras));
}
