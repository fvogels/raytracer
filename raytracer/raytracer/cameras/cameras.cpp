#include "cameras/cameras.h"
#include "cameras/perspective-camera.h"
#include "cameras/orthographic-camera.h"
#include "cameras/fisheye-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace math;


Matrix4D raytracer::cameras::create_transformation(const Point3D& eye, const Point3D& look_at, const Vector3D& up)
{
	Vector3D look_direction = (look_at - eye).normalized();
	Vector3D right = look_direction.cross(up).normalized();
	Vector3D fixed_up = right.cross(look_direction);

    assert(look_direction.is_unit());
	assert(right.is_unit());
	assert(fixed_up.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(right));

    Point3D origin = eye;    
    Vector3D y_axis = fixed_up;
    Vector3D z_axis = look_direction;
    Vector3D x_axis = y_axis.cross(z_axis);

    assert(x_axis.is_unit());
    assert(y_axis.is_unit());
    assert(z_axis.is_unit());
    assert(x_axis.is_perpendicular_on(y_axis));
    assert(x_axis.is_perpendicular_on(z_axis));
    assert(y_axis.is_perpendicular_on(z_axis));

	Matrix4D transformation = math::coordinate_system(origin, x_axis, y_axis, z_axis);

    assert(transformation * Vector3D(0, 1, 0) == approx<Vector3D>(up));
    assert(transformation * Vector3D(0, 0, 1) == approx<Vector3D>(look_direction));

	return transformation;
}

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
	Point3D view_window_origin(view_window_width / 2, -view_window_height / 2, distance);
	Vector3D view_window_right(-view_window_width, 0, 0);
	Vector3D view_window_up(0, view_window_height, 0);
	Rectangle3D view_window(view_window_origin, view_window_right, view_window_up);
	Matrix4D transformation = create_transformation(eye, look_at, up);
	
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
	Matrix4D transformation = create_transformation(eye, look_at, up);

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

	Matrix4D transformation = create_transformation(eye, look_at, up);

	return std::make_shared<FisheyeCamera>(transformation, horizontal_angle, vertical_angle);
}