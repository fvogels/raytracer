#ifdef TEST_BUILD

#include "Catch.h"
#include "math/quaternion.h"

using namespace math;


TEST_CASE("[Quaternions] Rotation around X-axis", "[Quaternions]")
{
    Vector3D axis = Vector3D::x_axis();

    SECTION("Rotating 90 degrees")
    {
        Angle angle = 90_degrees;
        Quaternion q = Quaternion::rotation(angle, axis);

        SECTION("Rotating point (0,0,0)")
        {
            Point3D p(0, 0, 0);
            Point3D expected(0, 0, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (1,0,0)")
        {
            Point3D p(1, 0, 0);
            Point3D expected(1, 0, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,1,0)")
        {
            Point3D p(0, 1, 0);
            Point3D expected(0, 0, 1);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,2,0)")
        {
            Point3D p(0, 2, 0);
            Point3D expected(0, 0, 2);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,0,1)")
        {
            Point3D p(0, 0, 1);
            Point3D expected(0, -1, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,0,5)")
        {
            Point3D p(0, 0, 5);
            Point3D expected(0, -5, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }
    }

    SECTION("Rotating 180 degrees")
    {
        Angle angle = 180_degrees;
        Quaternion q = Quaternion::rotation(angle, axis);

        SECTION("Rotating point (0,0,0)")
        {
            Point3D p(0, 0, 0);
            Point3D expected(0, 0, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (1,0,0)")
        {
            Point3D p(1, 0, 0);
            Point3D expected(1, 0, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,1,0)")
        {
            Point3D p(0, 1, 0);
            Point3D expected(0, -1, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,2,0)")
        {
            Point3D p(0, 2, 0);
            Point3D expected(0, -2, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,0,1)")
        {
            Point3D p(0, 0, 1);
            Point3D expected(0, 0, -1);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,0,5)")
        {
            Point3D p(0, 0, 5);
            Point3D expected(0, 0, -5);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }
    }
}

TEST_CASE("[Quaternions] Rotation around Y-axis", "[Quaternions]")
{
    Vector3D axis = Vector3D::y_axis();

    SECTION("Rotating 90 degrees")
    {
        Angle angle = 90_degrees;
        Quaternion q = Quaternion::rotation(angle, axis);

        SECTION("Rotating point (0,0,0)")
        {
            Point3D p(0, 0, 0);
            Point3D expected(0, 0, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (1,0,0)")
        {
            Point3D p(1, 0, 0);
            Point3D expected(0, 0, -1);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,1,0)")
        {
            Point3D p(0, 1, 0);
            Point3D expected(0, 1, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,2,0)")
        {
            Point3D p(0, 2, 0);
            Point3D expected(0, 2, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,0,1)")
        {
            Point3D p(0, 0, 1);
            Point3D expected(1, 0, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,0,5)")
        {
            Point3D p(0, 0, 5);
            Point3D expected(5, 0, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }
    }

    SECTION("Rotating 180 degrees")
    {
        Angle angle = 180_degrees;
        Quaternion q = Quaternion::rotation(angle, axis);

        SECTION("Rotating point (0,0,0)")
        {
            Point3D p(0, 0, 0);
            Point3D expected(0, 0, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (1,0,0)")
        {
            Point3D p(1, 0, 0);
            Point3D expected(-1, 0, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,1,0)")
        {
            Point3D p(0, 1, 0);
            Point3D expected(0, 1, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,2,0)")
        {
            Point3D p(0, 2, 0);
            Point3D expected(0, 2, 0);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,0,1)")
        {
            Point3D p(0, 0, 1);
            Point3D expected(0, 0, -1);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }

        SECTION("Rotating point (0,0,5)")
        {
            Point3D p(0, 0, 5);
            Point3D expected(0, 0, -5);
            Point3D actual = q.rotate(p);

            CHECK(actual == approx(expected));
        }
    }
}

#endif
