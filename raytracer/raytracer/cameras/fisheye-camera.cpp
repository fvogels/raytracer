#include "cameras/fisheye-camera.h"
#include "math/rectangle3d.h"
#include "math/angle.h"
#include <assert.h>

using namespace raytracer;
using namespace math;


raytracer::cameras::FisheyeCamera::FisheyeCamera(const math::Matrix4D& transformation)
	: DisplacableCamera(transformation)
{
	// NOP
}


Ray raytracer::cameras::FisheyeCamera::create_untransformed_ray(const Point2D& point) const
{
	assert(0 <= point.x && point.x <= 1);
	assert(0 <= point.y && point.y <= 1);

	Point3D eye(0, 0, 0);

	Angle azimuth = (0.5 - point.x) * 180_degrees - 90_degrees;
	Angle inclination = (1 - point.y) * 180_degrees;

	double x = sin(inclination) * cos(azimuth);
	double y = cos(inclination);
	double z = sin(inclination) * sin(azimuth);
	Point3D through(x, y, z);

	return Ray(eye, through);
}