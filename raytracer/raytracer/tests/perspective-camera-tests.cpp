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

        REQUIRE(approx<Point3D>(expected) == actual);
    }

    void assert_equals(const Vector3D& expected, const Vector3D& actual)
    {
        INFO("Expected: " << expected << "\nActual: " << actual);

        REQUIRE(approx<Vector3D>(expected) == actual);
    }

    std::string show(const Ray& ray)
    {
        std::ostringstream ss;

        ss << ray;

        return ss.str();
    }
}

#define XY(...)  __VA_ARGS__
#define XYZ(...) __VA_ARGS__

#define TEST_SIMPLE(P, EXPECTED_DIRECTION) \
    TEST(P, XYZ(0,0,0), XYZ(0,0,1), XYZ(0,1,0), 1, 1, XYZ(0,0,0), EXPECTED_DIRECTION)

#define TEST_DISTANCE_RATIO(P, DISTANCE, ASPECT_RATIO, EXPECTED_DIRECTION) \
    TEST(P, XYZ(0,0,0), XYZ(0,0,1), XYZ(0,1,0), DISTANCE, ASPECT_RATIO, XYZ(0,0,0), EXPECTED_DIRECTION)

#define TEST_EYE_LOOKAT(P, EYE, LOOK_AT, EXPECTED_DIRECTION) \
    TEST(P, EYE, LOOK_AT, XYZ(0,1,0), 1, 1, EYE, EXPECTED_DIRECTION)

#define TEST(P, EYE, LOOK_AT, UP, DISTANCE, ASPECT_RATIO, EXPECTED_ORIGIN, EXPECTED_DIRECTION) \
    TEST_CASE("[PerspectiveCamera] Eye = " #EYE ", Lookat = " #LOOK_AT ", Up = " #UP ", Distance = " #DISTANCE ", Aspect Ratio = " #ASPECT_RATIO ", At " #P, "[PerspectiveCamera]") \
    { \
        auto camera = raytracer::cameras::perspective(Point3D(EYE), Point3D(LOOK_AT), Vector3D(UP), DISTANCE, ASPECT_RATIO); \
        auto ray = camera->create_ray(Point2D(P)); \
        \
        INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(Point3D(EXPECTED_ORIGIN), Vector3D(EXPECTED_DIRECTION)))); \
        assert_equals(ray.origin, Point3D(EXPECTED_ORIGIN)); \
        assert_equals(ray.direction, Vector3D(EXPECTED_DIRECTION)); \
    }

TEST_SIMPLE(XY(0.5, 0.5), XYZ(0, 0, 1))
TEST_SIMPLE(XY(0, 0.5), XYZ(0.5, 0, 1))
TEST_SIMPLE(XY(1, 0.5), XYZ(-0.5, 0, 1))

TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(1, 0, 0), XYZ(1, 0, 1), XYZ(0, 0, 1))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(-1, 0, 0), XYZ(-1, 0, 1), XYZ(0, 0, 1))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(-2, 0, 0), XYZ(-2, 0, 1), XYZ(0, 0, 1))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(0, 0, 0), XYZ(1, 0, 0), XYZ(1, 0, 0))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(1, 0, 1), XYZ(0, 0, 0), XYZ(-sin(45_degrees), 0, -sin(45_degrees)))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(-1, 0, 1), XYZ(0, 0, 0), XYZ(sin(45_degrees), 0, -sin(45_degrees)))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(0, 0, 1), XYZ(0, 0, 0), XYZ(0, 0, -1))
TEST_EYE_LOOKAT(XY(0, 0.5), XYZ(0, 0, 1), XYZ(0, 0, 0), XYZ(-0.5, 0, -1))
TEST_EYE_LOOKAT(XY(1, 0.5), XYZ(0, 0, 1), XYZ(0, 0, 0), XYZ(0.5, 0, -1))
TEST_EYE_LOOKAT(XY(0, 0.5), XYZ(0, 0, 0), XYZ(0, 0, -1), XYZ(-0.5, 0, -1))

TEST_DISTANCE_RATIO(XY(0.5, 0.5), 0.5, 1, XYZ(0, 0, 0.5))

#endif
