#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[Plane] Hit between XY plane and (-2,-2,1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,-1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,1) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,1);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-1,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,1) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,1);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,-1,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,-5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,5) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,5);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(3,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,5) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,5);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,3,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,-10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,10) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,10);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(8,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,-2,10) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,10);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,8,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,-1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,1) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,1);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-1,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,1) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,1);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,1,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,-5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,5) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,5);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(3,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,5) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,5);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,5,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,-10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,10) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,10);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(8,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,0,10) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,10);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,10,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,-1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,1) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,1);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-1,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,1) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,1);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,3,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,-5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,5) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,5);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(3,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,5) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,5);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,7,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,-10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,10) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,10);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(8,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (-2,2,10) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,10);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,12,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,-1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,1) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,1);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(1,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,1) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,1);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-1,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,-5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,5) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,5);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(5,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,5) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,5);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,3,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,-10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,10) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,10);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(10,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,-2,10) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,10);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,8,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,-1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,1) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,1);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(1,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,1) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,1);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,1,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,-5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,5) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,5);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(5,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,5) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,5);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,5,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,-10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,10) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,10);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(10,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,0,10) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,10);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,10,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,-1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,1) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,1);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(1,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,1) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,1);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,3,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,-5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,5) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,5);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(5,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,5) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,5);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,7,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,-10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,10) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,10);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(10,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (0,2,10) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,10);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,12,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,-1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,1) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,1);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(3,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,1) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,1);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,-1,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,-5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,5) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,5);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(7,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,5) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,5);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,3,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,-10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,10) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,10);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(12,-2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,-2,10) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,10);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,8,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,-1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,1) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,1);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(3,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,1) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,1);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,1,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,-5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,5) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,5);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(7,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,5) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,5);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,5,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,-10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,10) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,10);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(12,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,0,10) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,10);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,10,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,-1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,1) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,1);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(3,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,1) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,1);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,3,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,-5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,5) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,5);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(7,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,5) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,5);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,7,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,-10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,10) + (1,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,10);
    Vector3D ray_direction(1,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(12,2,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] Hit between XY plane and (2,2,10) + (0,1,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,10);
    Vector3D ray_direction(0,1,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,12,0)));
    CHECK(hit.normal == approx(Vector3D(0,0,1).normalized()));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,1) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,1);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,-1) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-1);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,-1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,1) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,1);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,-1) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-1);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,5) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,5);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,-5) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-5);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,-5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,5) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,5);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,-5) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-5);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,10) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,10);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,-10) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-10);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,-10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,10) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,10);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,-2,-10) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(-2,-2,-10);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,1) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,1);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,-1) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-1);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,-1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,1) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,1);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,-1) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-1);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,5) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,5);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,-5) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-5);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,-5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,5) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,5);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,-5) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-5);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,10) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,10);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,-10) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-10);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,-10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,10) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,10);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,0,-10) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(-2,0,-10);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,1) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,1);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,-1) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-1);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,-1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,1) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,1);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,-1) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-1);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,5) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,5);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,-5) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-5);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,-5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,5) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,5);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,-5) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-5);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,10) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,10);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,-10) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-10);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,-10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,10) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,10);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (-2,2,-10) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(-2,2,-10);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,1) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,1);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,-1) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-1);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,-1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,1) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,1);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,-1) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-1);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,5) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,5);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,-5) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-5);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,-5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,5) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,5);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,-5) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-5);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,10) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,10);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,-10) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-10);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,-10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,10) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,10);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,-2,-10) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(0,-2,-10);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,1) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(0,0,1);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,-1) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-1);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,-1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,1) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(0,0,1);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,-1) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-1);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,5) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(0,0,5);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,-5) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-5);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,-5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,5) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(0,0,5);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,-5) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-5);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,10) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(0,0,10);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,-10) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-10);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,-10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,10) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(0,0,10);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,0,-10) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(0,0,-10);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,1) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(0,2,1);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,-1) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-1);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,-1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,1) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(0,2,1);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,-1) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-1);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,5) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(0,2,5);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,-5) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-5);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,-5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,5) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(0,2,5);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,-5) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-5);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,10) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(0,2,10);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,-10) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-10);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,-10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,10) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(0,2,10);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (0,2,-10) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(0,2,-10);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,1) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,1);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,-1) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-1);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,-1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,1) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,1);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,-1) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-1);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,5) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,5);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,-5) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-5);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,-5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,5) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,5);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,-5) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-5);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,10) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,10);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,-10) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-10);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,-10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,10) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,10);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,-2,-10) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(2,-2,-10);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,1) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(2,0,1);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,-1) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-1);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,-1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,1) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(2,0,1);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,-1) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-1);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,5) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(2,0,5);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,-5) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-5);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,-5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,5) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(2,0,5);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,-5) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-5);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,10) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(2,0,10);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,-10) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-10);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,-10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,10) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(2,0,10);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,0,-10) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(2,0,-10);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,1) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(2,2,1);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,-1) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-1);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,1) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,-1) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-1);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,1) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(2,2,1);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,-1) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-1);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,5) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(2,2,5);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,-5) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-5);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,5) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,5);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,-5) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-5);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,5) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(2,2,5);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,-5) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-5);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,10) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(2,2,10);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,-10) + (0,0,-0) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-10);
    Vector3D ray_direction(0,0,-0);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,10) + (0,0,1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,10);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,-10) + (0,0,-1) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-10);
    Vector3D ray_direction(0,0,-1);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,10) + (0,0,10) * t", "[Plane]")
{
    Point3D ray_origin(2,2,10);
    Vector3D ray_direction(0,0,10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between XY plane and (2,2,-10) + (0,0,-10) * t", "[Plane]")
{
    Point3D ray_origin(2,2,-10);
    Vector3D ray_direction(0,0,-10);

    auto primitive = raytracer::primitives::xy_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

#endif
