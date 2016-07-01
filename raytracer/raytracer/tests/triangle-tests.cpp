#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


namespace
{
    void test_hit(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& o, const Vector3D& d)
    {
        auto tri = triangle(a, b, c);
        Ray ray(o, d);
        Hit hit;

        REQUIRE(tri->find_hit(ray, &hit));
    }
}


#define XYZ(...) __VA_ARGS__

#define TEST_HIT(A, B, C, O, D) \
    TEST_CASE("[Triangle] Triangle " #A " " #B " " #C " is hit by ray " #O " + " #D + " * t", "[Triangle]") \
    { \
        test_hit( Point3D(A), Point3D(B), Point3D(C), Point3D(O), Vector3D(D)); \
    }

TEST_CASE("[Triangle] Hits against triangle with a = (0,0,0), b = (1,0,0), c = (0,1,0)", "[Triangle]")
{
    auto tri = triangle(Point3D(0, 0, 0), Point3D(1, 0, 0), Point3D(0, 1, 0));
    Hit hit;

    SECTION("ray (0.1,0.1,1) + (0,0,-1)")
    {
        Ray ray(Point3D(0.1, 0.1, 1), Vector3D(0, 0, -1));

        REQUIRE(tri->find_hit(ray, &hit));
    }

    SECTION("Ray (0.1,-0.1,1) + (0,0,-1)")
    {
        Ray ray(Point3D(0.1, -0.1, 1), Vector3D(0, 0, -1));

        REQUIRE(!tri->find_hit(ray, &hit));
    }

    SECTION("Ray (-0.1,0.1,1) + (0,0,-1)")
    {
        Ray ray(Point3D(-0.1, 0.1, 1), Vector3D(0, 0, -1));

        REQUIRE(!tri->find_hit(ray, &hit));
    }

    SECTION("Ray (0.9,0.05,1) + (0,0,-1)")
    {
        Ray ray(Point3D(0.9, 0.05, 1), Vector3D(0, 0, -1));

        REQUIRE(tri->find_hit(ray, &hit));
    }

    SECTION("Ray (0.05,0.9,1) + (0,0,-1)")
    {
        Ray ray(Point3D(0.05, 0.9, 1), Vector3D(0, 0, -1));

        REQUIRE(tri->find_hit(ray, &hit));
    }
}

#endif
