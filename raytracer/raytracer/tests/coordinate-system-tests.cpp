#ifdef TEST_BUILD

#include "Catch.h"
#include "math/coordinate-systems.h"
#include "math/angle.h"

using namespace math;


#define TEST_CARTESIAN3D_SPHERICAL(X,Y,Z,RADIUS,AZIMUTH,ELEVATION) \
    TEST_CASE("[CoordinateSystems] Conversion between Cartesian (" #X ", " #Y ", " #Z ") to Spherical (" #RADIUS ", " #AZIMUTH ", " #ELEVATION ")", "[CoordinateSystems]" ) \
    { \
        SECTION("Cartesian to Spherical") \
        { \
            Cartesian3D xyz{ X, Y, Z }; \
            auto spherical = convert_coordinates<Spherical>(xyz); \
            \
            CHECK(spherical.radius == Approx(RADIUS)); \
            CHECK(spherical.azimuth == approx(AZIMUTH)); \
            CHECK(spherical.elevation == approx(ELEVATION)); \
        }\
        SECTION("Spherical to Cartesian") \
        { \
            Spherical spherical{ RADIUS, AZIMUTH, ELEVATION }; \
            auto cartesian = convert_coordinates<Cartesian3D>(spherical); \
            \
            CHECK(cartesian.x == Approx(X)); \
            CHECK(cartesian.y == Approx(Y)); \
            CHECK(cartesian.z == Approx(Z)); \
        } \
    }

TEST_CARTESIAN3D_SPHERICAL(0, 0, 0, 0, 0_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(1, 0, 0, 1, 0_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(2, 0, 0, 2, 0_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(3, 0, 0, 3, 0_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(-3, 0, 0, 3, 180_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 1, 0, 1, 0_degrees, 90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 2, 0, 2, 0_degrees, 90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 3, 0, 3, 0_degrees, 90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, -1, 0, 1, 0_degrees, -90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, -2, 0, 2, 0_degrees, -90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, -3, 0, 3, 0_degrees, -90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, 1, 1, 90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, 2, 2, 90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, 3, 3, 90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, -1, 1, -90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, -2, 2, -90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, -3, 3, -90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(1, 0, 1, sqrt(2), 45_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(-1, 0, 1, sqrt(2), 135_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(1, 0, -1, sqrt(2), -45_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(-1, 0, -1, sqrt(2), -135_degrees, 0_degrees)

#endif
