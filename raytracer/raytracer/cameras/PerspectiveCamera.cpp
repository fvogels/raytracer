#include "cameras/PerspectiveCamera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace Raytracer;
using namespace math;

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(const point3d& eye, const rectangle3d& view_window);

	virtual Ray create_Ray(const point2d&) const override;

private:
	point3d eye;
	rectangle3d view_window;
};

PerspectiveCamera::PerspectiveCamera(const point3d& eye, const rectangle3d& view_window)
	: eye(eye), view_window(view_window)
{
	// NOP
}

Ray PerspectiveCamera::create_Ray(const point2d& point) const
{
	assert(0 <= point.x && point.x <= 1);
	assert(0 <= point.y && point.y <= 1);

	point3d p = view_window.project(point);

	return Ray(eye, p);
}

std::shared_ptr<Camera> Raytracer::create_perspective_camera(
	const math::point3d& eye,
	const math::point3d& look_at,
	const math::vector3d& up,
	double distance,
	double aspect_ratio)
{
	assert(up.is_unit());

	vector3d look_direction = (look_at - eye).normalized();
	point3d view_window_center = eye + look_direction;

	vector3d right = look_direction.cross(up);

	assert(right.is_unit());
	assert(up.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(up));

	point3d view_window_origin = view_window_center + up / 2 - right / 2 * aspect_ratio;
	vector3d view_window_down = -up;
	vector3d view_window_right = right * aspect_ratio;

	rectangle3d view_window(view_window_origin, view_window_right, view_window_down);

	return std::make_shared<PerspectiveCamera>(eye, view_window);
}