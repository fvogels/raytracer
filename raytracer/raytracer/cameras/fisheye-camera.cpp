#include "cameras/fisheye-camera.h"
#include "math/rectangle3d.h"
#include "math/angle.h"
#include <assert.h>

using namespace raytracer;
using namespace math;


raytracer::cameras::FisheyeCamera::FisheyeCamera(const math::Matrix4D& transformation, math::Angle horizontal_angle, math::Angle vertical_angle)
	: DisplacableCamera(transformation), m_horizontal_angle(horizontal_angle), m_vertical_angle(vertical_angle)
{
	// NOP
}

Ray raytracer::cameras::FisheyeCamera::create_untransformed_ray(const Point2D& point) const
{
	assert(0 <= point.x && point.x <= 1);
	assert(0 <= point.y && point.y <= 1);

	Point3D eye(0, 0, 0);

	double dx = point.x - 0.5;
	Angle azimuth_zero = -90_degrees;
	Angle delta_azimuth = -dx * m_horizontal_angle;
	Angle azimuth = azimuth_zero + delta_azimuth;

	double dy = point.y - 0.5;
	Angle inclination_zero = 90_degrees;
	Angle delta_inclination = -dy * m_vertical_angle;
	Angle inclination = inclination_zero + delta_inclination;

	double x = sin(inclination) * cos(azimuth);
	double y = cos(inclination);
	double z = sin(inclination) * sin(azimuth);
	Point3D through(x, y, z);

	return Ray(eye, through);
}