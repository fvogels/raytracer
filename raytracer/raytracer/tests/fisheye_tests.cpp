#ifdef TEST_BUILD

#include "Catch.h"
#include "cameras/cameras.h"

using namespace math;


void assert_equals(const Point3D& p, const Point3D& q)
{
	REQUIRE(p.x == Approx(q.x));
	REQUIRE(p.y == Approx(q.y));
	REQUIRE(p.z == Approx(q.z));
}

void assert_equals(const Vector3D& u, const Vector3D& v)
{
	REQUIRE(u.x == Approx(v.x));
	REQUIRE(u.y == Approx(v.y));
	REQUIRE(u.z == Approx(v.z));
}

TEST_CASE("[FisheyeCamera] At (0.5, 0.5)", "[FisheyeCamera]")
{
	auto camera = raytracer::cameras::create_fisheye_camera();
	auto ray = camera->create_ray(Point2D(0.5, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 0, 1));
}

TEST_CASE("[FisheyeCamera] At (1, 0.5)", "[FisheyeCamera]")
{
	auto camera = raytracer::cameras::create_fisheye_camera();
	auto ray = camera->create_ray(Point2D(1, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(1, 0, 0));
}

TEST_CASE("[FisheyeCamera] At (0, 0.5)", "[FisheyeCamera]")
{
	auto camera = raytracer::cameras::create_fisheye_camera();
	auto ray = camera->create_ray(Point2D(0, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(-1, 0, 0));
}

TEST_CASE("[FisheyeCamera] At (0.5, 1)", "[FisheyeCamera]")
{
	auto camera = raytracer::cameras::create_fisheye_camera();
	auto ray = camera->create_ray(Point2D(0.5, 1));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 1, 0));
}

TEST_CASE("[FisheyeCamera] At (0.5, 0)", "[FisheyeCamera]")
{
	auto camera = raytracer::cameras::create_fisheye_camera();
	auto ray = camera->create_ray(Point2D(0.5, 0));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, -1, 0));
}

#endif
