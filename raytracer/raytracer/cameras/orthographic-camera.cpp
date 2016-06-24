#include "cameras/orthographic-camera.h"
#include "math/rectangle3d.h"
#include <assert.h>

using namespace raytracer;
using namespace math;

raytracer::cameras::OrthographicCamera::OrthographicCamera(const Rectangle3D& eye_window, const Rectangle3D& view_window)
	: eye_window(eye_window), view_window(view_window)
{
	// NOP
}

Ray raytracer::cameras::OrthographicCamera::create_ray(const Point2D& point) const
{
	assert(0 <= point.x && point.x <= 1);
	assert(0 <= point.y && point.y <= 1);

	Point3D from = eye_window.project(point);
	Point3D through = view_window.project(point);

	return Ray(from, through);
}