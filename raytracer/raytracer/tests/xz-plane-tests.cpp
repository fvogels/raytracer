#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[Plane] Hit between XZ plane and (-2,1,-2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,1,-2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,-1,-2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-1,-2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,1,-2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,1,-2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-1,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,1,-2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,1,-2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,-1)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,5,-2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,5,-2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,-5,-2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-5,-2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,5,-2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,5,-2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(3,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,5,-2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,5,-2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,3)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,10,-2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,10,-2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,-10,-2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-10,-2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,10,-2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,10,-2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(8,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,10,-2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,10,-2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,8)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,1,0) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,1,0);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,-1,0) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-1,0);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,1,0) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,1,0);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-1,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,1,0) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,1,0);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,1)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,5,0) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,5,0);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,-5,0) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-5,0);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,5,0) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,5,0);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(3,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,5,0) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,5,0);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,5)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,10,0) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,10,0);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,-10,0) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-10,0);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,10,0) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,10,0);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(8,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,10,0) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,10,0);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,10)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,1,2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,1,2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,-1,2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-1,2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,1,2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,1,2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-1,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,1,2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,1,2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(-2,0,3)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,5,2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,5,2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,-5,2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-5,2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,5,2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,5,2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(3,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,5,2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,5,2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(-2,0,7)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,10,2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,10,2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,-10,2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,-10,2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,10,2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(-2,10,2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(8,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (-2,10,2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(-2,10,2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(-2,0,12)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,1,-2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,1,-2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,-1,-2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-1,-2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,1,-2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,1,-2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(1,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,1,-2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(0,1,-2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,-1)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,5,-2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,5,-2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,-5,-2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-5,-2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,5,-2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,5,-2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(5,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,5,-2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(0,5,-2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,3)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,10,-2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,10,-2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,-10,-2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-10,-2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,10,-2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,10,-2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(10,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,10,-2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(0,10,-2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,8)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,1,0) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,1,0);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,-1,0) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-1,0);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,1,0) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,1,0);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(1,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,1,0) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(0,1,0);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,1)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,5,0) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,5,0);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,-5,0) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-5,0);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,5,0) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,5,0);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(5,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,5,0) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(0,5,0);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,5)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,10,0) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,10,0);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,-10,0) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-10,0);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,10,0) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,10,0);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(10,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,10,0) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(0,10,0);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,10)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,1,2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,1,2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,-1,2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-1,2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,1,2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,1,2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(1,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,1,2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(0,1,2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,3)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,5,2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,5,2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,-5,2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-5,2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,5,2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,5,2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(5,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,5,2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(0,5,2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,7)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,10,2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,10,2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,-10,2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,-10,2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,10,2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(0,10,2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(10,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (0,10,2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(0,10,2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,12)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,1,-2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,1,-2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,-1,-2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-1,-2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,1,-2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,1,-2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(3,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,1,-2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(2,1,-2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,-1)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,5,-2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,5,-2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,-5,-2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-5,-2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,5,-2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,5,-2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(7,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,5,-2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(2,5,-2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,3)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,10,-2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,10,-2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,-10,-2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-10,-2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,10,-2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,10,-2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(12,0,-2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,10,-2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(2,10,-2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,8)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,1,0) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,1,0);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,-1,0) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-1,0);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,1,0) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,1,0);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(3,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,1,0) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(2,1,0);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,1)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,5,0) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,5,0);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,-5,0) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-5,0);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,5,0) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,5,0);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(7,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,5,0) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(2,5,0);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,5)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,10,0) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,10,0);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,-10,0) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-10,0);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,10,0) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,10,0);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(12,0,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,10,0) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(2,10,0);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,10)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,1,2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,1,2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,-1,2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-1,2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,1,2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,1,2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(3,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,1,2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(2,1,2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(2,0,3)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,5,2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,5,2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,-5,2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-5,2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,5,2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,5,2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(7,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,5,2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(2,5,2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,7)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,10,2) + (0,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,10,2);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,-10,2) + (0,1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,-10,2);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,10,2) + (1,-1,0) * t", "[Plane]")
{
    Point3D ray_origin(2,10,2);
    Vector3D ray_direction(1,-1,0);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(12,0,2)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

TEST_CASE("[Plane] Hit between XZ plane and (2,10,2) + (0,-1,1) * t", "[Plane]")
{
    Point3D ray_origin(2,10,2);
    Vector3D ray_direction(0,-1,1);

    auto primitive = raytracer::primitives::xz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(2,0,12)));
    CHECK(hit.normal == approx(Vector3D(0,1,0).normalized()));
}

#endif
