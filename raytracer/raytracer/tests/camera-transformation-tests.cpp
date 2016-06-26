#ifdef TEST_BUILD

#include "Catch.h"
#include "cameras/cameras.h"

using namespace math;
using namespace raytracer::cameras;

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
}

#define XYZ(...) __VA_ARGS__
#define TEST(EYE, LOOK_AT, UP, P, EXPECTED)		TEST_CASE("[CameraTransformation] Eye = " #EYE", Lookat = " #LOOK_AT ", Up = " #UP ", p = " #P, "[CameraTransformation]") \
                                                { \
                                                    auto matrix = create_transformation(Point3D(EYE), Point3D(LOOK_AT), Vector3D(UP)); \
                                                    Point3D p(P); \
                                                    Point3D actual = matrix * p; \
                                                    Point3D expected(EXPECTED); \
                                                    assert_equals(actual, expected); \
                                                }


TEST(XYZ(0, 0, 0), XYZ(0, 0, 1), XYZ(0, 1, 0), XYZ(0, 0, 0), XYZ(0, 0, 0))
TEST(XYZ(0, 0, 1), XYZ(0, 0, 2), XYZ(0, 1, 0), XYZ(0, 0, 0), XYZ(0, 0, 1))
TEST(XYZ(1, 0, 0), XYZ(1, 0, 1), XYZ(0, 1, 0), XYZ(0, 0, 0), XYZ(1, 0, 0))
TEST(XYZ(1, 0, 0), XYZ(3, 5, 8), XYZ(0, 1, 0), XYZ(0, 0, 0), XYZ(1, 0, 0))
TEST(XYZ(0, 0, 0), XYZ(1, 0, 0), XYZ(0, 1, 0), XYZ(0, 0, 1), XYZ(1, 0, 0))
TEST(XYZ(0, 0, 0), XYZ(0, 1, 0), XYZ(0, 0, 1), XYZ(0, 0, 1), XYZ(0, 1, 0))
TEST(XYZ(0, 0, 0), XYZ(0, 0, 1), XYZ(0, 1, 0), XYZ(0, 0, 1), XYZ(0, 0, 1))

#endif
