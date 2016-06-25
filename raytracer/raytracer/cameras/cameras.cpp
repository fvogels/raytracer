#include "cameras/cameras.h"
#include "cameras/perspective-camera.h"
#include "cameras/orthographic-camera.h"
#include "cameras/fisheye-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace math;


std::shared_ptr<Camera> raytracer::cameras::perspective(
	const math::Point3D& eye,
	const math::Point3D& look_at,
	const math::Vector3D& up,
	double distance,
	double aspect_ratio)
{
	assert(up.is_unit());

	double view_window_width = aspect_ratio;
	double view_window_height = 1;
	Point3D view_window_origin(- view_window_width / 2, -view_window_height / 2, -distance);
	Vector3D view_window_right(view_window_width, 0, 0);
	Vector3D view_window_up(0, view_window_height, 0);
	Rectangle3D view_window(view_window_origin, view_window_right, view_window_up);

	Vector3D look_direction = (look_at - eye).normalized();
	Vector3D back_direction = -look_direction;
	Vector3D right = look_direction.cross(up).normalized();
	Vector3D fixed_up = right.cross(look_direction);

	assert(look_direction.is_unit());
	assert(right.is_unit());
	assert(fixed_up.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(right));

	Matrix4D transformation = math::coordinate_system(eye, right, fixed_up, back_direction);
	
	return std::make_shared<PerspectiveCamera>(transformation, view_window);
}

std::shared_ptr<Camera> raytracer::cameras::orthographic(
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

	Point3D eye_window_origin = eye - up2 * window_height / 2 - right * window_width / 2;
	Vector3D eye_window_right = right * window_width;
	Vector3D eye_window_up = up2 * window_height;
	Rectangle3D eye_window(eye_window_origin, eye_window_right, eye_window_up);

	Vector3D eye_view_offset = look_direction;
	Point3D view_window_origin = eye_window_origin + eye_view_offset;
	Vector3D view_window_right = eye_window_right;
	Vector3D view_window_up = eye_window_up;
	Rectangle3D view_window(view_window_origin, view_window_right, view_window_up);

	return std::make_shared<OrthographicCamera>(eye_window, view_window);
}

std::shared_ptr<Camera> raytracer::cameras::fisheye()
{
	return std::make_shared<FisheyeCamera>();
}