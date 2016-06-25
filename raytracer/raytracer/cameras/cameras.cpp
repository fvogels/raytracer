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
	Vector3D back_direction = -look_direction;
	Vector3D right = look_direction.cross(up).normalized();
	Vector3D fixed_up = right.cross(look_direction);

	assert(look_direction.is_unit());
	assert(right.is_unit());
	assert(fixed_up.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(right));

	Matrix4D transformation = math::coordinate_system(eye, right, fixed_up, back_direction);

	return std::make_shared<OrthographicCamera>(transformation, window_width, window_height);
}

std::shared_ptr<Camera> raytracer::cameras::fisheye(
	const math::Point3D& eye,
	const math::Point3D& look_at,
	const math::Vector3D& up,
	const math::Angle& horizontal_angle,
	const math::Angle& vertical_angle)
{
	assert(up.is_unit());

	Vector3D look_direction = (look_at - eye).normalized();
	Vector3D back_direction = -look_direction;
	Vector3D right = look_direction.cross(up).normalized();
	Vector3D fixed_up = right.cross(look_direction);

	assert(look_direction.is_unit());
	assert(right.is_unit());
	assert(fixed_up.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(right));

	Matrix4D transformation = math::coordinate_system(eye, right, fixed_up, back_direction);

	return std::make_shared<FisheyeCamera>(transformation, horizontal_angle, vertical_angle);
}