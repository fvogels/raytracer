#ifdef TEST_BUILD

#include "Catch.h"
#include "cameras/cameras.h"

using namespace math;

namespace
{
    void assert_equals(const Point3D& expected, const Point3D& actual)
    {
        INFO("Expected: " << expected << "\nActual: " << actual);

        REQUIRE(approx(expected) == actual);
    }

    void assert_equals(const Vector3D& expected, const Vector3D& actual)
    {
        INFO("Expected: " << expected << "\nActual: " << actual);

        REQUIRE(approx(expected) == actual);
    }

    std::string show(const Ray& ray)
    {
        std::ostringstream ss;

        ss << ray;

        return ss.str();
    }
}

TEST_CASE("[FisheyeCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), HAngle = 180, VAngle = 180, At (0.5,0.5)", "[FisheyeCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 180_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), HAngle = 180, VAngle = 180, At (0,0.5)", "[FisheyeCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 180_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(1,0,0);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), HAngle = 180, VAngle = 180, At (1,0.5)", "[FisheyeCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 180_degrees;
    Angle vangle = 180_degrees;
    Point2D position(1,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(-1,0,0);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), HAngle = 180, VAngle = 180, At (0.5,1)", "[FisheyeCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 180_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0.5,1);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,1,0);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), HAngle = 180, VAngle = 180, At (0.5,0)", "[FisheyeCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 180_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0.5,0);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,-1,0);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (1,0,0), Lookat = (1,0,1), Up = (0,1,0), HAngle = 180, VAngle = 180, At (0.5,0.5)", "[FisheyeCamera]")
{
    Point3D eye(1,0,0);
    Point3D look_at(1,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 180_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0.5,0.5);
    Point3D expected_origin(1,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (-1,0,0), Lookat = (-1,0,1), Up = (0,1,0), HAngle = 180, VAngle = 180, At (0.5,0.5)", "[FisheyeCamera]")
{
    Point3D eye(-1,0,0);
    Point3D look_at(-1,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 180_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0.5,0.5);
    Point3D expected_origin(-1,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (-2,0,0), Lookat = (-2,0,1), Up = (0,1,0), HAngle = 180, VAngle = 180, At (0.5,0.5)", "[FisheyeCamera]")
{
    Point3D eye(-2,0,0);
    Point3D look_at(-2,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 180_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0.5,0.5);
    Point3D expected_origin(-2,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (0,0,0), Lookat = (1,0,0), Up = (0,1,0), HAngle = 180, VAngle = 180, At (0.5,0.5)", "[FisheyeCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(1,0,0);
    Vector3D up(0,1,0);
    Angle hangle = 180_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(1,0,0);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), HAngle = 360, VAngle = 180, At (0.5,0.5)", "[FisheyeCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 360_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), HAngle = 360, VAngle = 180, At (1,0.5)", "[FisheyeCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 360_degrees;
    Angle vangle = 180_degrees;
    Point2D position(1,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,-1);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


TEST_CASE("[FisheyeCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), HAngle = 360, VAngle = 180, At (0,0.5)", "[FisheyeCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    Angle hangle = 360_degrees;
    Angle vangle = 180_degrees;
    Point2D position(0,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,-1);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}


#endif
