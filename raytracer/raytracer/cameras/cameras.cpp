#include "cameras/cameras.h"
#include "cameras/perspective-camera.h"
#include "cameras/orthographic-camera.h"
#include "cameras/fisheye-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace math;


std::shared_ptr<Camera> raytracer::cameras::create_perspective_camera(
	const math::Point3D& eye,
	const math::Point3D& look_at,
	const math::Vector3D& up,
	double distance,
	double aspect_ratio)
{
	assert(up.is_unit());

	Vector3D look_direction = (look_at - eye).normalized();
	Vector3D right = look_direction.cross(up).normalized();
	Vector3D up2 = right.cross(look_direction);

	assert(look_direction.is_unit());
	assert(right.is_unit());
	assert(up2.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(right));

	Point3D view_window_center = eye + look_direction * distance;
	Point3D view_window_origin = view_window_center + up2 / 2 - right / 2 * aspect_ratio;
	Vector3D view_window_down = -up2;
	Vector3D view_window_right = right * aspect_ratio;

	Rectangle3D view_window(view_window_origin, view_window_right, view_window_down);

	return std::make_shared<PerspectiveCamera>(eye, view_window);
}

std::shared_ptr<Camera> raytracer::cameras::create_orthographic_camera(
	const math::Point3D& eye,
	const math::Point3D& look_at,
	const math::Vector3D& up,
	double window_width,
	double aspect_ratio)
{
	assert(up.is_unit());

	double window_height = window_width / aspect_ratio;

	Vector3D look_direction = (look_at - eye).normalized();
	Vector3D right = look_direction.cross(up).normalized();
	Vector3D up2 = right.cross(look_direction);

	assert(look_direction.is_unit());
	assert(right.is_unit());
	assert(up2.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(right));

	Point3D eye_window_origin = eye + up2 * window_height / 2 - right * window_width / 2;
	Vector3D eye_window_right = right * window_width;
	Vector3D eye_window_down = -up2 * window_height;
	Rectangle3D eye_window(eye_window_origin, eye_window_right, eye_window_down);

	Vector3D eye_view_offset = look_direction;
	Point3D view_window_origin = eye_window_origin + eye_view_offset;
	Vector3D view_window_right = eye_window_right;
	Vector3D view_window_down = eye_window_down;
	Rectangle3D view_window(view_window_origin, view_window_right, view_window_down);

	return std::make_shared<OrthographicCamera>(eye_window, view_window);
}

std::shared_ptr<Camera> raytracer::cameras::create_fisheye_camera()
{
	return std::make_shared<FisheyeCamera>();
}