#include "cameras/perspective-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace math;

namespace
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(const Point3D& eye, const Rectangle3D& view_window)
			: m_eye(eye), m_view_window(view_window)
		{
			// NOP
		}

		Ray create_Ray(const Point2D& point) const override
		{
			assert(0 <= point.x && point.x <= 1);
			assert(0 <= point.y && point.y <= 1);

			Point3D p = m_view_window.project(point);

			return Ray(m_eye, p);
		}

	private:
		Point3D m_eye;
		Rectangle3D m_view_window;
	};
}

std::shared_ptr<Camera> raytracer::create_perspective_camera(
	const math::Point3D& eye,
	const math::Point3D& look_at,
	const math::Vector3D& up,
	double distance,
	double aspect_ratio)
{
	assert(up.is_unit());

	Vector3D look_direction = (look_at - eye).normalized();
	Point3D view_window_center = eye + look_direction;

	Vector3D right = look_direction.cross(up).normalized();
	Vector3D up2 = right.cross(look_direction);

	assert(look_direction.is_unit());
	assert(right.is_unit());
	assert(up2.is_perpendicular_on(right));
	assert(look_direction.is_perpendicular_on(right));

	Point3D view_window_origin = view_window_center + up2 / 2 - right / 2 * aspect_ratio;
	Vector3D view_window_down = -up2;
	Vector3D view_window_right = right * aspect_ratio;

	Rectangle3D view_window(view_window_origin, view_window_right, view_window_down);

	return std::make_shared<PerspectiveCamera>(eye, view_window);
}