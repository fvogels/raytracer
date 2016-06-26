#include "cameras/perspective-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace math;


raytracer::cameras::PerspectiveCamera::PerspectiveCamera(const math::Matrix4D transformation, const Rectangle3D& view_window)
    : DisplacableCamera(transformation), m_view_window(view_window)
{
    // NOP
}

Ray raytracer::cameras::PerspectiveCamera::create_untransformed_ray(const Point2D& point) const
{
    assert(0 <= point.x && point.x <= 1);
    assert(0 <= point.y && point.y <= 1);

    Point3D p = m_view_window.project(point);

    return Ray(Point3D(0, 0, 0), p);
}