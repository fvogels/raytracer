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

#define XY(...)  __VA_ARGS__
#define XYZ(...) __VA_ARGS__

#define TEST_SIMPLE(P, EXPECTED_DIRECTION) \
    TEST(P, XYZ(0,0,0), XYZ(0,0,1), XYZ(0,1,0), 180, 180, XYZ(0,0,0), EXPECTED_DIRECTION)

#define TEST_EYE_LOOKAT(P, EYE, LOOK_AT, EXPECTED_DIRECTION) \
    TEST(P, EYE, LOOK_AT, XYZ(0,1,0), 180, 180, EYE, EXPECTED_DIRECTION)

#define TEST_ANGLES(P, HANGLE, VANGLE, EXPECTED_DIRECTION) \
    TEST(P, XYZ(0,0,0), XYZ(0,0,1), XYZ(0,1,0), HANGLE, VANGLE, XYZ(0,0,0), EXPECTED_DIRECTION)

#define TEST(P, EYE, LOOK_AT, UP, HANGLE, VANGLE, EXPECTED_ORIGIN, EXPECTED_DIRECTION) \
    TEST_CASE("[FisheyeCamera] Eye = " #EYE ", Lookat = " #LOOK_AT ", Up = " #UP ", HAngle = " #HANGLE ", VAngle = " #VANGLE ", At " #P, "[FisheyeCamera]") \
    { \
        auto camera = raytracer::cameras::fisheye(Point3D(EYE), Point3D(LOOK_AT), Vector3D(UP), degrees(HANGLE), degrees(VANGLE)); \
        auto rays = camera->create_rays(Point2D(P)); \
        \
        REQUIRE(rays.size() == 1); \
        auto ray = rays.front(); \
        INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(Point3D(EXPECTED_ORIGIN), Vector3D(EXPECTED_DIRECTION)))); \
        assert_equals(ray.origin, Point3D(EXPECTED_ORIGIN)); \
        assert_equals(ray.direction, Vector3D(EXPECTED_DIRECTION)); \
    }

TEST_SIMPLE(XY(0.5, 0.5), XYZ(0, 0, 1))
TEST_SIMPLE(XY(0, 0.5), XYZ(1, 0, 0))
TEST_SIMPLE(XY(1, 0.5), XYZ(-1, 0, 0))
TEST_SIMPLE(XY(0.5, 1), XYZ(0, 1, 0))
TEST_SIMPLE(XY(0.5, 0), XYZ(0, -1, 0))

TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(1, 0, 0), XYZ(1, 0, 1), XYZ(0, 0, 1))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(-1, 0, 0), XYZ(-1, 0, 1), XYZ(0, 0, 1))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(-2, 0, 0), XYZ(-2, 0, 1), XYZ(0, 0, 1))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(0, 0, 0), XYZ(1, 0, 0), XYZ(1, 0, 0))

TEST_ANGLES(XY(0.5, 0.5), 360, 180, XYZ(0, 0, 1))
TEST_ANGLES(XY(1, 0.5), 360, 180, XYZ(0, 0, -1))
TEST_ANGLES(XY(0, 0.5), 360, 180, XYZ(0, 0, -1))

#endif
