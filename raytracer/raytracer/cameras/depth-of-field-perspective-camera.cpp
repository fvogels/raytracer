#include "cameras/depth-of-field-perspective-camera.h"
#include "cameras/perspective-camera.h"
#include "cameras/displaceable-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::cameras;
using namespace raytracer::samplers;
using namespace math;


namespace
{
    class DepthOfFieldPerspectiveCamera : public raytracer::cameras::_private_::DisplaceableCamera
    {
    public:
        DepthOfFieldPerspectiveCamera(const math::Matrix4x4 transformation, const std::vector<Camera>& cameras)
            : DisplaceableCamera(transformation), m_cameras(cameras)
        {
            // NOP
        }

    protected:
        void enumerate_untransformed_rays(const Point2D& point, std::function<void(const math::Ray&)> callback) const
        {
            assert(interval(0, 1).contains(point.x()));
            assert(interval(0, 1).contains(point.y()));

            for (auto& camera : m_cameras)
            {
                camera->enumerate_rays(point, callback);
            }
        }

    private:
        std::vector<Camera> m_cameras;
    };
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

    Matrix4x4 transformation = _private_::create_transformation(eye, look_at, up);
    Point3D canonical_look_at = Point3D(0, 0, math::distance(eye, look_at));

    std::vector<Camera> cameras;
    Rectangle2D eye_area(Point2D(-eye_size / 2, -eye_size / 2), Vector2D(eye_size, 0), Vector2D(0, eye_size));
    eye_sampler->sample(eye_area, [&cameras, &canonical_look_at, distance, aspect_ratio](Point2D eye) {
        cameras.push_back(perspective(Point3D(eye.x(), eye.y(), 0), canonical_look_at, Vector3D(0, 1, 0), distance, aspect_ratio));
    });

    return Camera(std::make_shared<DepthOfFieldPerspectiveCamera>(transformation, cameras));
}
