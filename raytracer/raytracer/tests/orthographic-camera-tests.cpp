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

TEST_CASE("[OrthographicCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Window Width = 1, Aspect Ratio = 1, At (0.5,0.5)", "[OrthographicCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    double window_width = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[OrthographicCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Window Width = 1, Aspect Ratio = 1, At (1,0.5)", "[OrthographicCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    double window_width = 1;
    double aspect_ratio = 1;
    Point2D position(1,0.5);
    Point3D expected_origin(-0.5,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[OrthographicCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Window Width = 1, Aspect Ratio = 1, At (0,0.5)", "[OrthographicCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    double window_width = 1;
    double aspect_ratio = 1;
    Point2D position(0,0.5);
    Point3D expected_origin(0.5,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[OrthographicCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Window Width = 1, Aspect Ratio = 1, At (0.5,1)", "[OrthographicCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    double window_width = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,1);
    Point3D expected_origin(0,0.5,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[OrthographicCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Window Width = 1, Aspect Ratio = 1, At (0.5,0)", "[OrthographicCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up(0,1,0);
    double window_width = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0);
    Point3D expected_origin(0,-0.5,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[OrthographicCamera] Eye = (1,0,0), Lookat = (1,0,1), Up = (0,1,0), Window Width = 1, Aspect Ratio = 1, At (0.5,0.5)", "[OrthographicCamera]")
{
    Point3D eye(1,0,0);
    Point3D look_at(1,0,1);
    Vector3D up(0,1,0);
    double window_width = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(1,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[OrthographicCamera] Eye = (-1,0,0), Lookat = (-1,0,1), Up = (0,1,0), Window Width = 1, Aspect Ratio = 1, At (0.5,0.5)", "[OrthographicCamera]")
{
    Point3D eye(-1,0,0);
    Point3D look_at(-1,0,1);
    Vector3D up(0,1,0);
    double window_width = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(-1,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[OrthographicCamera] Eye = (-2,0,0), Lookat = (-2,0,1), Up = (0,1,0), Window Width = 1, Aspect Ratio = 1, At (0.5,0.5)", "[OrthographicCamera]")
{
    Point3D eye(-2,0,0);
    Point3D look_at(-2,0,1);
    Vector3D up(0,1,0);
    double window_width = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(-2,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[OrthographicCamera] Eye = (0,0,0), Lookat = (1,0,0), Up = (0,1,0), Window Width = 1, Aspect Ratio = 1, At (0.5,0.5)", "[OrthographicCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(1,0,0);
    Vector3D up(0,1,0);
    double window_width = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(1,0,0);

    auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


#endif
