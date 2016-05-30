#include "cameras/perspective-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace Raytracer;
using namespace math;

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(const Point3D& eye, const Rectangle3D& view_window);

	virtual Ray create_Ray(const Point2D&) const override;

private:
	Point3D eye;
	Rectangle3D view_window;
};

PerspectiveCamera::PerspectiveCamera(const Point3D& eye, const Rectangle3D& view_window)
	: eye(eye), view_window(view_window)
{
	// NOP
}

Ray PerspectiveCamera::create_Ray(const Point2D& point) const
{
	assert(0 <= point.x && point.x <= 1);
	assert(0 <= point.y && point.y <= 1);

	Point3D p = view_window.project(point);

	return Ray(eye, p);
}

std::shared_ptr<Camera> Raytracer::create_perspective_camera(
	const math::Point3D& eye,
	const math::Point3D& look_at,
	const math::Vector3D& up,
	double distance,
	double aspect_ratio)
{
	assert(up.is_unit());

	Vector3D look_direction = (look_at - eye).normalized();
	Point3D view_window_center = eye + look_direction;

	Vector3D right = look_direction.cross(up);

	assert(right.is_unit());
	assert(up.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(up));

	Point3D view_window_origin = view_window_center + up / 2 - right / 2 * aspect_ratio;
	Vector3D view_window_down = -up;
	Vector3D view_window_right = right * aspect_ratio;

	Rectangle3D view_window(view_window_origin, view_window_right, view_window_down);

	return std::make_shared<PerspectiveCamera>(eye, view_window);
}