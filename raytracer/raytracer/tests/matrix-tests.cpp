#ifdef TEST_BUILD

#include "Catch.h"
#include "math/matrix.h"
#include "math/transformation-matrices.h"

using namespace math;
using namespace math::transformation_matrices;


TEST_CASE("[Matrix] Matrix transformation identity<4>() equals identity<4>()", "[Matrix]")
{
    auto a = identity<4>();
    auto b = identity<4>();

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation translation(Vector3D(0,0,0)) equals identity<4>()", "[Matrix]")
{
    auto a = translation(Vector3D(0,0,0));
    auto b = identity<4>();

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation scaling(1,1,1) equals identity<4>()", "[Matrix]")
{
    auto a = scaling(1,1,1);
    auto b = identity<4>();

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation rotation_around_x(0_degrees) equals identity<4>()", "[Matrix]")
{
    auto a = rotation_around_x(0_degrees);
    auto b = identity<4>();

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation rotation_around_y(0_degrees) equals identity<4>()", "[Matrix]")
{
    auto a = rotation_around_y(0_degrees);
    auto b = identity<4>();

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation rotation_around_z(0_degrees) equals identity<4>()", "[Matrix]")
{
    auto a = rotation_around_z(0_degrees);
    auto b = identity<4>();

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation rotation_around_x(0_degrees) equals rotation_around_x(360_degrees)", "[Matrix]")
{
    auto a = rotation_around_x(0_degrees);
    auto b = rotation_around_x(360_degrees);

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation rotation_around_x(-90_degrees) equals rotation_around_x(270_degrees)", "[Matrix]")
{
    auto a = rotation_around_x(-90_degrees);
    auto b = rotation_around_x(270_degrees);

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation rotation_around_x(-180_degrees) equals rotation_around_x(180_degrees)", "[Matrix]")
{
    auto a = rotation_around_x(-180_degrees);
    auto b = rotation_around_x(180_degrees);

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation scaling(-1,1,-1) equals rotation_around_y(180_degrees)", "[Matrix]")
{
    auto a = scaling(-1,1,-1);
    auto b = rotation_around_y(180_degrees);

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation scaling(-1,-1,1) equals rotation_around_z(180_degrees)", "[Matrix]")
{
    auto a = scaling(-1,-1,1);
    auto b = rotation_around_z(180_degrees);

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix transformation scaling(1,-1,-1) equals rotation_around_x(180_degrees)", "[Matrix]")
{
    auto a = scaling(1,-1,-1);
    auto b = rotation_around_x(180_degrees);

    REQUIRE( a == approx(b) );
}

TEST_CASE("[Matrix] Matrix multiplication of identity<4>() and identity<4>()", "[Matrix]")
{
    auto a = identity<4>();
    auto b = identity<4>();
    auto actual = a * b;
    auto expected = identity<4>();

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of identity<4>() and scaling(2, 1, 1)", "[Matrix]")
{
    auto a = identity<4>();
    auto b = scaling(2, 1, 1);
    auto actual = a * b;
    auto expected = scaling(2, 1, 1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of identity<4>() and scaling(1, 3, 1)", "[Matrix]")
{
    auto a = identity<4>();
    auto b = scaling(1, 3, 1);
    auto actual = a * b;
    auto expected = scaling(1, 3, 1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of identity<4>() and scaling(1, 1, 4)", "[Matrix]")
{
    auto a = identity<4>();
    auto b = scaling(1, 1, 4);
    auto actual = a * b;
    auto expected = scaling(1, 1, 4);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of identity<4>() and rotation_around_x(40_degrees)", "[Matrix]")
{
    auto a = identity<4>();
    auto b = rotation_around_x(40_degrees);
    auto actual = a * b;
    auto expected = rotation_around_x(40_degrees);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of identity<4>() and rotation_around_y(10_degrees)", "[Matrix]")
{
    auto a = identity<4>();
    auto b = rotation_around_y(10_degrees);
    auto actual = a * b;
    auto expected = rotation_around_y(10_degrees);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of identity<4>() and rotation_around_z(250_degrees)", "[Matrix]")
{
    auto a = identity<4>();
    auto b = rotation_around_z(250_degrees);
    auto actual = a * b;
    auto expected = rotation_around_z(250_degrees);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of scaling(2, 1, 1) and scaling(2, 1, 1)", "[Matrix]")
{
    auto a = scaling(2, 1, 1);
    auto b = scaling(2, 1, 1);
    auto actual = a * b;
    auto expected = scaling(4, 1, 1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of scaling(2, 1, 1) and scaling(0.5, 1, 1)", "[Matrix]")
{
    auto a = scaling(2, 1, 1);
    auto b = scaling(0.5, 1, 1);
    auto actual = a * b;
    auto expected = scaling(1, 1, 1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of scaling(2, 1, 1) and scaling(1, 2, 1)", "[Matrix]")
{
    auto a = scaling(2, 1, 1);
    auto b = scaling(1, 2, 1);
    auto actual = a * b;
    auto expected = scaling(2, 2, 1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of scaling(2, 1, 1) and scaling(1, 1, 2)", "[Matrix]")
{
    auto a = scaling(2, 1, 1);
    auto b = scaling(1, 1, 2);
    auto actual = a * b;
    auto expected = scaling(2, 1, 2);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of scaling(1, 3, 1) and scaling(1, 1, 2)", "[Matrix]")
{
    auto a = scaling(1, 3, 1);
    auto b = scaling(1, 1, 2);
    auto actual = a * b;
    auto expected = scaling(1, 3, 2);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_x(10_degrees) and rotation_around_x(10_degrees)", "[Matrix]")
{
    auto a = rotation_around_x(10_degrees);
    auto b = rotation_around_x(10_degrees);
    auto actual = a * b;
    auto expected = rotation_around_x(20_degrees);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_x(10_degrees) and rotation_around_x(-10_degrees)", "[Matrix]")
{
    auto a = rotation_around_x(10_degrees);
    auto b = rotation_around_x(-10_degrees);
    auto actual = a * b;
    auto expected = identity<4>();

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_x(10_degrees) and rotation_around_x(20_degrees)", "[Matrix]")
{
    auto a = rotation_around_x(10_degrees);
    auto b = rotation_around_x(20_degrees);
    auto actual = a * b;
    auto expected = rotation_around_x(30_degrees);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_y(10_degrees) and rotation_around_y(20_degrees)", "[Matrix]")
{
    auto a = rotation_around_y(10_degrees);
    auto b = rotation_around_y(20_degrees);
    auto actual = a * b;
    auto expected = rotation_around_y(30_degrees);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_z(10_degrees) and rotation_around_z(20_degrees)", "[Matrix]")
{
    auto a = rotation_around_z(10_degrees);
    auto b = rotation_around_z(20_degrees);
    auto actual = a * b;
    auto expected = rotation_around_z(30_degrees);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(1,0,0)) and translation(Vector3D(-1,0,0))", "[Matrix]")
{
    auto a = translation(Vector3D(1,0,0));
    auto b = translation(Vector3D(-1,0,0));
    auto actual = a * b;
    auto expected = identity<4>();

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(0,5,0)) and translation(Vector3D(0,-5,0))", "[Matrix]")
{
    auto a = translation(Vector3D(0,5,0));
    auto b = translation(Vector3D(0,-5,0));
    auto actual = a * b;
    auto expected = identity<4>();

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(0,0,9)) and translation(Vector3D(0,0,-9))", "[Matrix]")
{
    auto a = translation(Vector3D(0,0,9));
    auto b = translation(Vector3D(0,0,-9));
    auto actual = a * b;
    auto expected = identity<4>();

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(1,0,0)) and translation(Vector3D(0,0,2))", "[Matrix]")
{
    auto a = translation(Vector3D(1,0,0));
    auto b = translation(Vector3D(0,0,2));
    auto actual = a * b;
    auto expected = translation(Vector3D(1,0,2));

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(1,0,0)) and Vector3D(0,0,0)", "[Matrix]")
{
    auto a = translation(Vector3D(1,0,0));
    auto b = Vector3D(0,0,0);
    auto actual = a * b;
    auto expected = Vector3D(0,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(0,1,0)) and Vector3D(0,0,0)", "[Matrix]")
{
    auto a = translation(Vector3D(0,1,0));
    auto b = Vector3D(0,0,0);
    auto actual = a * b;
    auto expected = Vector3D(0,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(0,0,1)) and Vector3D(0,0,0)", "[Matrix]")
{
    auto a = translation(Vector3D(0,0,1));
    auto b = Vector3D(0,0,0);
    auto actual = a * b;
    auto expected = Vector3D(0,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(1,0,0)) and Point3D(0,0,0)", "[Matrix]")
{
    auto a = translation(Vector3D(1,0,0));
    auto b = Point3D(0,0,0);
    auto actual = a * b;
    auto expected = Point3D(1,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(0,1,0)) and Point3D(0,0,0)", "[Matrix]")
{
    auto a = translation(Vector3D(0,1,0));
    auto b = Point3D(0,0,0);
    auto actual = a * b;
    auto expected = Point3D(0,1,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of translation(Vector3D(0,0,1)) and Point3D(0,0,0)", "[Matrix]")
{
    auto a = translation(Vector3D(0,0,1));
    auto b = Point3D(0,0,0);
    auto actual = a * b;
    auto expected = Point3D(0,0,1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of scaling(2,1,1) and Point3D(0,0,0)", "[Matrix]")
{
    auto a = scaling(2,1,1);
    auto b = Point3D(0,0,0);
    auto actual = a * b;
    auto expected = Point3D(0,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of scaling(2,1,1) and Point3D(1,0,0)", "[Matrix]")
{
    auto a = scaling(2,1,1);
    auto b = Point3D(1,0,0);
    auto actual = a * b;
    auto expected = Point3D(2,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of scaling(2,3,4) and Point3D(1,1,1)", "[Matrix]")
{
    auto a = scaling(2,3,4);
    auto b = Point3D(1,1,1);
    auto actual = a * b;
    auto expected = Point3D(2,3,4);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of scaling(2,3,4) and Point3D(2,2,2)", "[Matrix]")
{
    auto a = scaling(2,3,4);
    auto b = Point3D(2,2,2);
    auto actual = a * b;
    auto expected = Point3D(4,6,8);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_x(180_degrees) and Point3D(2,2,2)", "[Matrix]")
{
    auto a = rotation_around_x(180_degrees);
    auto b = Point3D(2,2,2);
    auto actual = a * b;
    auto expected = Point3D(2,-2,-2);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_y(180_degrees) and Point3D(2,2,2)", "[Matrix]")
{
    auto a = rotation_around_y(180_degrees);
    auto b = Point3D(2,2,2);
    auto actual = a * b;
    auto expected = Point3D(-2,2,-2);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_z(180_degrees) and Point3D(2,2,2)", "[Matrix]")
{
    auto a = rotation_around_z(180_degrees);
    auto b = Point3D(2,2,2);
    auto actual = a * b;
    auto expected = Point3D(-2,-2,2);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_x(180_degrees) and Vector3D(2,2,2)", "[Matrix]")
{
    auto a = rotation_around_x(180_degrees);
    auto b = Vector3D(2,2,2);
    auto actual = a * b;
    auto expected = Vector3D(2,-2,-2);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_y(180_degrees) and Vector3D(2,2,2)", "[Matrix]")
{
    auto a = rotation_around_y(180_degrees);
    auto b = Vector3D(2,2,2);
    auto actual = a * b;
    auto expected = Vector3D(-2,2,-2);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_z(180_degrees) and Vector3D(2,2,2)", "[Matrix]")
{
    auto a = rotation_around_z(180_degrees);
    auto b = Vector3D(2,2,2);
    auto actual = a * b;
    auto expected = Vector3D(-2,-2,2);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_x(90_degrees) and Point3D(0,0,0)", "[Matrix]")
{
    auto a = rotation_around_x(90_degrees);
    auto b = Point3D(0,0,0);
    auto actual = a * b;
    auto expected = Point3D(0,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_x(90_degrees) and Point3D(1,0,0)", "[Matrix]")
{
    auto a = rotation_around_x(90_degrees);
    auto b = Point3D(1,0,0);
    auto actual = a * b;
    auto expected = Point3D(1,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_x(90_degrees) and Point3D(0,1,0)", "[Matrix]")
{
    auto a = rotation_around_x(90_degrees);
    auto b = Point3D(0,1,0);
    auto actual = a * b;
    auto expected = Point3D(0,0,1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_x(90_degrees) and Point3D(0,0,1)", "[Matrix]")
{
    auto a = rotation_around_x(90_degrees);
    auto b = Point3D(0,0,1);
    auto actual = a * b;
    auto expected = Point3D(0,-1,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_y(90_degrees) and Point3D(0,0,0)", "[Matrix]")
{
    auto a = rotation_around_y(90_degrees);
    auto b = Point3D(0,0,0);
    auto actual = a * b;
    auto expected = Point3D(0,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_y(90_degrees) and Point3D(0,1,0)", "[Matrix]")
{
    auto a = rotation_around_y(90_degrees);
    auto b = Point3D(0,1,0);
    auto actual = a * b;
    auto expected = Point3D(0,1,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_y(90_degrees) and Point3D(1,0,0)", "[Matrix]")
{
    auto a = rotation_around_y(90_degrees);
    auto b = Point3D(1,0,0);
    auto actual = a * b;
    auto expected = Point3D(0,0,-1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_y(90_degrees) and Point3D(0,0,-1)", "[Matrix]")
{
    auto a = rotation_around_y(90_degrees);
    auto b = Point3D(0,0,-1);
    auto actual = a * b;
    auto expected = Point3D(-1,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_y(90_degrees) and Point3D(-1,0,0)", "[Matrix]")
{
    auto a = rotation_around_y(90_degrees);
    auto b = Point3D(-1,0,0);
    auto actual = a * b;
    auto expected = Point3D(0,0,1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_z(90_degrees) and Point3D(0,0,0)", "[Matrix]")
{
    auto a = rotation_around_z(90_degrees);
    auto b = Point3D(0,0,0);
    auto actual = a * b;
    auto expected = Point3D(0,0,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_z(90_degrees) and Point3D(0,0,1)", "[Matrix]")
{
    auto a = rotation_around_z(90_degrees);
    auto b = Point3D(0,0,1);
    auto actual = a * b;
    auto expected = Point3D(0,0,1);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_z(90_degrees) and Point3D(1,0,0)", "[Matrix]")
{
    auto a = rotation_around_z(90_degrees);
    auto b = Point3D(1,0,0);
    auto actual = a * b;
    auto expected = Point3D(0,1,0);

    REQUIRE( actual == approx(expected) );
}

TEST_CASE("[Matrix] Matrix multiplication of rotation_around_z(90_degrees) and Point3D(0,1,0)", "[Matrix]")
{
    auto a = rotation_around_z(90_degrees);
    auto b = Point3D(0,1,0);
    auto actual = a * b;
    auto expected = Point3D(-1,0,0);

    REQUIRE( actual == approx(expected) );
}

#endif
