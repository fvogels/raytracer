#ifdef TEST_BUILD

#include "Catch.h"
#include "math/coordinate-systems.h"
#include "math/angle.h"

using namespace math;


TEST_CASE("[CoordinateSystems] Cartesian (0, 0, 0) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 0, 0, 0 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(0));   
}

TEST_CASE("[CoordinateSystems] Cartesian (1, 0, 0) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 1, 0, 0 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(1));
    CHECK(spherical.azimuth == approx(0_degrees));
    CHECK(spherical.elevation == approx(0_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (2, 0, 0) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 2, 0, 0 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(2));
    CHECK(spherical.azimuth == approx(0_degrees));
    CHECK(spherical.elevation == approx(0_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (3, 0, 0) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 3, 0, 0 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(3));
    CHECK(spherical.azimuth == approx(0_degrees));
    CHECK(spherical.elevation == approx(0_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (0, 1, 0) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 0, 1, 0 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(1));
    CHECK(spherical.azimuth == approx(0_degrees));
    CHECK(spherical.elevation == approx(90_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (0, 2, 0) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 0, 2, 0 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(2));
    CHECK(spherical.azimuth == approx(0_degrees));
    CHECK(spherical.elevation == approx(90_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (0, -1, 0) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 0, -1, 0 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(1));
    CHECK(spherical.azimuth == approx(0_degrees));
    CHECK(spherical.elevation == approx(-90_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (0, -2, 0) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 0, -2, 0 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(2));
    CHECK(spherical.azimuth == approx(0_degrees));
    CHECK(spherical.elevation == approx(-90_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (0, 0, 1) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 0, 0, 1 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(1));
    CHECK(spherical.azimuth == approx(90_degrees));
    CHECK(spherical.elevation == approx(0_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (0, 0, 2) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 0, 0, 2 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(2));
    CHECK(spherical.azimuth == approx(90_degrees));
    CHECK(spherical.elevation == approx(0_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (0, 0, -1) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 0, 0, -1 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(1));
    CHECK(spherical.azimuth == approx(-90_degrees));
    CHECK(spherical.elevation == approx(0_degrees));
}

TEST_CASE("[CoordinateSystems] Cartesian (0, 0, -2) to SphericalRAE", "[CoordinateSystems]")
{
    Cartesian3D xyz{ 0, 0, -2 };
    auto spherical = convert_coordinates<SphericalRAE>(xyz);

    CHECK(spherical.radius == Approx(2));
    CHECK(spherical.azimuth == approx(-90_degrees));
    CHECK(spherical.elevation == approx(0_degrees));
}

#endif
