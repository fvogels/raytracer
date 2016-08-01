#ifdef TEST_BUILD

#include "Catch.h"
#include "cameras/cameras.h"

using namespace math;
using namespace raytracer::cameras::_private_;

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

    void assert_equals(const Matrix4D& a, const Matrix4D& b)
    {
#define EQ(row, col) REQUIRE(a.x ## row ## col == Approx(b.x ## row ## col))
        EQ(1, 1);
        EQ(1, 2);
        EQ(1, 3);
        EQ(1, 4);

        EQ(2, 1);
        EQ(2, 2);
        EQ(2, 3);
        EQ(2, 4);

        EQ(3, 1);
        EQ(3, 2);
        EQ(3, 3);
        EQ(3, 4);

        EQ(4, 1);
        EQ(4, 2);
        EQ(4, 3);
        EQ(4, 4);
#undef EQ
    }
}

#define XYZ(...) __VA_ARGS__

TEST_CASE("[CameraTransformation] Eye = (0,0,0), Lookat = (0,0,1), Up = (0,1,0)", "[CameraTransformation]")
{
    Point3D eye(0, 0, 0);
    Point3D lookat(0, 0, 1);
    Vector3D up(0, 1, 0);

    auto matrix = create_transformation(eye, lookat, up);
    auto expected = math::transformation_matrices::identity();

    assert_equals(matrix, expected);
    assert_equals(eye, matrix * Point3D(0, 0, 0));
    assert_equals(lookat, matrix * Point3D(0, 0, 1));
    assert_equals(up, matrix * Vector3D(0, 1, 0));
}

TEST_CASE("[CameraTransformation] Eye = (1,0,0), Lookat = (1,0,1), Up = (0,1,0)", "[CameraTransformation]")
{
    Point3D eye(1, 0, 0);
    Point3D lookat(1, 0, 1);
    Vector3D up(0, 1, 0);

    auto matrix = create_transformation(eye, lookat, up);

    assert_equals(eye, matrix * Point3D(0, 0, 0));
    assert_equals(lookat, matrix * Point3D(0, 0, 1));
    assert_equals(up, matrix * Vector3D(0, 1, 0));
}

TEST_CASE("[CameraTransformation] Eye = (0,0,0), Lookat = (1,0,0), Up = (0,1,0)", "[CameraTransformation]")
{
    Point3D eye(0, 0, 0);
    Point3D lookat(1, 0, 0);
    Vector3D up(0, 1, 0);

    auto matrix = create_transformation(eye, lookat, up);

    assert_equals(matrix * Point3D(0, 0, 0), eye);
    assert_equals(matrix * Point3D(0, 0, 1), lookat);
    assert_equals(matrix * Vector3D(0, 1, 0), up);
}

TEST_CASE("[CameraTransformation] Eye = (0,0,1), Lookat = (0,0,0), Up = (0,1,0)", "[CameraTransformation]")
{
    Point3D eye(0, 0, 0);
    Point3D lookat(1, 0, 0);
    Vector3D up(0, 1, 0);

    auto matrix = create_transformation(eye, lookat, up);

    assert_equals(matrix * Point3D(0, 0, 0), eye);
    assert_equals(matrix * Point3D(0, 0, 1), lookat);
    assert_equals(matrix * Vector3D(0, 1, 0), up);
}

#endif
