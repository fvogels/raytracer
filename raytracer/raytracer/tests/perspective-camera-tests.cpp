#ifdef TEST_BUILD

#include "Catch.h"
#include "cameras/cameras.h"
#include <sstream>
#include <string>

using namespace math;


namespace
{
    void assert_equals(const Point3D& expected, const Point3D& actual)
    {
        INFO("Expected Point3D: " << expected << "\nActual: " << actual);

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

TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0.5,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (1,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(1,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(-0.5,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,1)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,1);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0.5,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,0)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,-0.5,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (1,0,0), Lookat = (1,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(1,0,0);
    Point3D look_at(1,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(1,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (-1,0,0), Lookat = (-1,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(-1,0,0);
    Point3D look_at(-1,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(-1,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (-2,0,0), Lookat = (-2,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(-2,0,0);
    Point3D look_at(-2,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(-2,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (1,0,0), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(1,0,0);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(1,0,0);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (1,0,1), Lookat = (0,0,0), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(1,0,1);
    Point3D look_at(0,0,0);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(1,0,1);
    Vector3D expected_direction(-sin(45_degrees),0,-sin(45_degrees));

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (-1,0,1), Lookat = (0,0,0), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(-1,0,1);
    Point3D look_at(0,0,0);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(-1,0,1);
    Vector3D expected_direction(sin(45_degrees),0,-sin(45_degrees));

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,1), Lookat = (0,0,0), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,1);
    Point3D look_at(0,0,0);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,1);
    Vector3D expected_direction(0,0,-1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,1), Lookat = (0,0,0), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,1);
    Point3D look_at(0,0,0);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0,0.5);
    Point3D expected_origin(0,0,1);
    Vector3D expected_direction(-0.5,0,-1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,1), Lookat = (0,0,0), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (1,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,1);
    Point3D look_at(0,0,0);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(1,0.5);
    Point3D expected_origin(0,0,1);
    Vector3D expected_direction(0.5,0,-1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,-1), Up = (0,1,0), Distance = 1, Aspect Ratio = 1, At (0,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,-1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(-0.5,0,-1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 0.5, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 0.5;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,0.5);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 2, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 2;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,2);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 2, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 2;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 2, At (0.5,1)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 2;
    Point2D position(0.5,1);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0.5,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 2, At (0.5,0)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 2;
    Point2D position(0.5,0);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,-0.5,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 2, At (0,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 2;
    Point2D position(0,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(1,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0), Distance = 1, Aspect Ratio = 2, At (1,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(0,1,0).normalized();
    double distance = 1;
    double aspect_ratio = 2;
    Point2D position(1,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(-1,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (1,0,0), Distance = 1, Aspect Ratio = 1, At (0.5,0.5)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(1,0,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0.5,0.5);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0,0,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (1,0,0), Distance = 1, Aspect Ratio = 1, At (0,0)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(1,0,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0,0);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(-0.5,-0.5,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (1,0,0), Distance = 1, Aspect Ratio = 1, At (1,0)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(1,0,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(1,0);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(-0.5,0.5,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (1,0,0), Distance = 1, Aspect Ratio = 1, At (0,1)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(1,0,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(0,1);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0.5,-0.5,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


TEST_CASE("[PerspectiveCamera] Eye = (0,0,0), Lookat = (0,0,1), Up = (1,0,0), Distance = 1, Aspect Ratio = 1, At (1,1)", "[PerspectiveCamera]")
{
    Point3D eye(0,0,0);
    Point3D look_at(0,0,1);
    Vector3D up = Vector3D(1,0,0).normalized();
    double distance = 1;
    double aspect_ratio = 1;
    Point2D position(1,1);
    Point3D expected_origin(0,0,0);
    Vector3D expected_direction(0.5,0.5,1);

    auto camera = raytracer::cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)) );
    assert_equals(ray.origin, Point3D(expected_origin));
    assert_equals(ray.direction, Vector3D(expected_direction));
}


#endif
