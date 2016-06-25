#ifdef TEST_BUILD

#include "Catch.h"
#include "cameras/cameras.h"

using namespace math;

namespace
{
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

	std::shared_ptr<raytracer::Camera> create_default_camera()
	{
		return raytracer::cameras::fisheye(Point3D(0, 0, 0), Point3D(0, 0, 1), Vector3D(0, 1, 0), 180_degrees, 180_degrees);
	}

	std::shared_ptr<raytracer::Camera> create_camera_with_hangle(Angle angle)
	{
		return raytracer::cameras::fisheye(Point3D(0, 0, 0), Point3D(0, 0, 1), Vector3D(0, 1, 0), angle, 180_degrees);
	}
}

TEST_CASE("[FisheyeCamera] At (0.5, 0.5)", "[FisheyeCamera]")
{
	auto camera = create_default_camera();
	auto ray = camera->create_ray(Point2D(0.5, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 0, 1));
}

TEST_CASE("[FisheyeCamera] At (1, 0.5)", "[FisheyeCamera]")
{
	auto camera = create_default_camera();
	auto ray = camera->create_ray(Point2D(1, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(1, 0, 0));
}

TEST_CASE("[FisheyeCamera] At (0, 0.5)", "[FisheyeCamera]")
{
	auto camera = create_default_camera();
	auto ray = camera->create_ray(Point2D(0, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(-1, 0, 0));
}

TEST_CASE("[FisheyeCamera] At (0.5, 1)", "[FisheyeCamera]")
{
	auto camera = create_default_camera();
	auto ray = camera->create_ray(Point2D(0.5, 1));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 1, 0));
}

TEST_CASE("[FisheyeCamera] At (0.5, 0)", "[FisheyeCamera]")
{
	auto camera = create_default_camera();
	auto ray = camera->create_ray(Point2D(0.5, 0));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, -1, 0));
}

TEST_CASE("[FisheyeCamera] At (0.5, 0.5) with horizontal angle = 90", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(90_degrees);
	auto ray = camera->create_ray(Point2D(0.5, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 0, 1));
}

TEST_CASE("[FisheyeCamera] At (1, 0.5) with horizontal angle = 90", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(90_degrees);
	auto ray = camera->create_ray(Point2D(1, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(sin(45_degrees), 0, sin(45_degrees)));
}

TEST_CASE("[FisheyeCamera] At (0, 0.5) with horizontal angle = 90", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(90_degrees);
	auto ray = camera->create_ray(Point2D(0, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(-sin(45_degrees), 0, sin(45_degrees)));
}

TEST_CASE("[FisheyeCamera] At (0.5, 1) with horizontal angle = 90", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(90_degrees);
	auto ray = camera->create_ray(Point2D(0.5, 1));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 1, 0));
}

TEST_CASE("[FisheyeCamera] At (0.5, 0) with horizontal angle = 90", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(90_degrees);
	auto ray = camera->create_ray(Point2D(0.5, 0));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, -1, 0));
}

TEST_CASE("[FisheyeCamera] At (0.5, 0.5) with horizontal angle = 360", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(360_degrees);
	auto ray = camera->create_ray(Point2D(0.5, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 0, 1));
}

TEST_CASE("[FisheyeCamera] At (1, 0.5) with horizontal angle = 360", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(360_degrees);
	auto ray = camera->create_ray(Point2D(1, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 0, -1));
}

TEST_CASE("[FisheyeCamera] At (0, 0.5) with horizontal angle = 360", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(360_degrees);
	auto ray = camera->create_ray(Point2D(0, 0.5));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 0, -1));
}

TEST_CASE("[FisheyeCamera] At (0.5, 1) with horizontal angle = 360", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(360_degrees);
	auto ray = camera->create_ray(Point2D(0.5, 1));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, 1, 0));
}

TEST_CASE("[FisheyeCamera] At (0.5, 0) with horizontal angle = 360", "[FisheyeCamera]")
{
	auto camera = create_camera_with_hangle(360_degrees);
	auto ray = camera->create_ray(Point2D(0.5, 0));

	assert_equals(ray.origin, Point3D(0, 0, 0));
	assert_equals(ray.direction, Vector3D(0, -1, 0));
}

#endif
