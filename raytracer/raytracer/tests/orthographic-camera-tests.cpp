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

    std::string show(const Ray& ray)
    {
        std::ostringstream ss;

        ss << ray;

        return ss.str();
    }
}

#define XY(...)  __VA_ARGS__
#define XYZ(...) __VA_ARGS__

#define TEST_SIMPLE(P, EXPECTED_ORIGIN, EXPECTED_DIRECTION)	\
    TEST_EYE_LOOKAT(P, XYZ(0,0,0), XYZ(0,0,1), EXPECTED_ORIGIN, EXPECTED_DIRECTION)

#define TEST_EYE_LOOKAT(P, EYE, LOOK_AT, EXPECTED_ORIGIN, EXPECTED_DIRECTION) \
    TEST(P, EYE, LOOK_AT, XYZ(0,1,0), 1, 1, EXPECTED_ORIGIN, EXPECTED_DIRECTION)

#define TEST(P, EYE, LOOK_AT, UP, WINDOW_WIDTH, ASPECT_RATIO, EXPECTED_ORIGIN, EXPECTED_DIRECTION) \
    TEST_CASE("[OrthographicCamera] Eye = " #EYE ", Lookat = " #LOOK_AT ", Up = " #UP ", Window Width = " #WINDOW_WIDTH ", Aspect Ratio =" #ASPECT_RATIO ", At " #P, "[OrthographicCamera]") \
    { \
        auto camera = raytracer::cameras::orthographic(Point3D(EYE), Point3D(LOOK_AT), Vector3D(UP), WINDOW_WIDTH, ASPECT_RATIO); \
        auto ray = camera->create_ray(Point2D(P)); \
        \
        INFO( "Actual ray: " + show(ray) ); \
        assert_equals(ray.origin, Point3D(EXPECTED_ORIGIN)); \
        assert_equals(ray.direction, Vector3D(EXPECTED_DIRECTION)); \
    }


TEST_SIMPLE(XY(0.5, 0.5), XYZ(0, 0, 0), XYZ(0, 0, 1))
TEST_SIMPLE(XY(1, 0.5), XYZ(0.5, 0, 0), XYZ(0, 0, 1))
TEST_SIMPLE(XY(0, 0.5), XYZ(-0.5, 0, 0), XYZ(0, 0, 1))
TEST_SIMPLE(XY(0.5, 1), XYZ(0, 0.5, 0), XYZ(0, 0, 1))
TEST_SIMPLE(XY(0.5, 0), XYZ(0, -0.5, 0), XYZ(0, 0, 1))

TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(1, 0, 0), XYZ(1, 0, 1), XYZ(1, 0, 0), XYZ(0, 0, 1))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(-1, 0, 0), XYZ(-1, 0, 1), XYZ(-1, 0, 0), XYZ(0, 0, 1))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(-2, 0, 0), XYZ(-2, 0, 1), XYZ(-2, 0, 0), XYZ(0, 0, 1))
TEST_EYE_LOOKAT(XY(0.5, 0.5), XYZ(0, 0, 0), XYZ(1, 0, 0), XYZ(0, 0, 0), XYZ(1, 0, 0))

#endif
