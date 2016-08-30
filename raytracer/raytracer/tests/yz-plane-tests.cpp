#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[Plane] Hit between YZ plane and (1,-2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-1,-2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,-2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,-2,-2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,-2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-1,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,-2,-2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,-2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,-1)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,-2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-5,-2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,-2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,-2,-2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,-2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,3,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,-2,-2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,-2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,3)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,-2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-10,-2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,-2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,-2,-2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,-2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,8,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,-2,-2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,-2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,8)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,-2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-1,-2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,-2,0) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,0);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-1,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,-2,0) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,0);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,1)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,-2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-5,-2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,-2,0) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,0);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,3,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,-2,0) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,0);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,5)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,-2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-10,-2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,-2,0) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,0);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,8,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,-2,0) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,0);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,10)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,-2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-1,-2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,-2,2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-1,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,-2,2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-2,3)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,-2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-5,-2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,-2,2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,3,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,-2,2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,-2,7)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,-2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-10,-2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,-2,2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,8,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,-2,2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,-2,12)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,0,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-1,0,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,0,-2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,-2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,1,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,0,-2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(1,0,-2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,-1)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,0,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-5,0,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,0,-2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,-2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,5,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,0,-2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(5,0,-2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,3)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,0,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-10,0,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,-2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,0,-2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,-2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,10,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,0,-2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(10,0,-2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,8)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,0,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-1,0,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,0,0) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,0);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,1,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,0,0) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(1,0,0);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,1)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,0,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-5,0,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,0,0) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,0);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,5,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,0,0) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(5,0,0);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,5)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,0,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-10,0,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,0,0) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,0);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,10,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,0,0) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(10,0,0);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,10)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,0,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-1,0,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,0,2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,1,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,0,2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(1,0,2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,0,3)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,0,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-5,0,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,0,2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,5,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,0,2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(5,0,2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,0,7)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,0,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-10,0,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,0,2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,10,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,0,2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(10,0,2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,0,12)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-1,2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,-2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,2,-2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,-2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,3,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,2,-2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(1,2,-2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,-1)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-5,2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,-2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,2,-2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,-2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,7,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,2,-2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(5,2,-2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,3)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-10,2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,-2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,2,-2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,-2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,12,-2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,2,-2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(10,2,-2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,8)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-1,2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,2,0) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,0);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,3,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,2,0) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(1,2,0);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,1)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-5,2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,2,0) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,0);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,7,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,2,0) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(5,2,0);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,5)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-10,2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,2,0) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,0);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,12,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,2,0) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(10,2,0);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,10)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-1,2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,2,2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,3,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (1,2,2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(1,2,2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,2,3)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-5,2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,2,2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,7,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (5,2,2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(5,2,2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(0,2,7)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (-10,2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,2)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,2,2) + (-1,1,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,2);
    Vector3D ray_direction(-1,1,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,12,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] Hit between YZ plane and (10,2,2) + (-1,0,1) * t", "[Plane]")
{
    Point3D ray_origin(10,2,2);
    Vector3D ray_direction(-1,0,1);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(10));
    CHECK(hit.position == approx(Point3D(0,2,12)));
    CHECK(hit.normal == approx(Vector3D(1,0,0).normalized()));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,-2,-2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,-2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,-2,-2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,-2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,-2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,-2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,-2,-2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,-2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,-2,-2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,-2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,-2,-2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,-2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,-2,-2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,-2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,-2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,-2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,-2,-2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,-2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,-2,-2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,-2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,-2,-2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,-2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,-2,-2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,-2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,-2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,-2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,-2,-2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,-2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,-2,-2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,-2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,-2,0) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,0);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,-2,0) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,0);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,-2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,-2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,-2,0) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,0);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,-2,0) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,0);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,-2,0) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,0);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,-2,0) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,0);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,-2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,-2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,-2,0) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,0);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,-2,0) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,0);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,-2,0) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,0);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,-2,0) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,0);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,-2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,-2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,-2,0) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,0);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,-2,0) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,0);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,-2,2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,-2,2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,-2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,-2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,-2,2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,-2,2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,-2,2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,-2,2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,-2,2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,-2,2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,-2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,-2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,-2,2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,-2,2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,-2,2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,-2,2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,-2,2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,-2,2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,-2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,-2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,-2,2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,-2,2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,-2,2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,-2,2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,0,-2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,-2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,0,-2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,-2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,0,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,0,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,0,-2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,-2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,0,-2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,-2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,0,-2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,-2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,0,-2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,-2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,0,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,0,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,0,-2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,-2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,0,-2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,-2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,0,-2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,-2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,0,-2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,-2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,0,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,0,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,0,-2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,-2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,0,-2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,-2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,0,0) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,0);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,0,0) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,0);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,0,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,0,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,0,0) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,0);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,0,0) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,0);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,0,0) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,0);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,0,0) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,0);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,0,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,0,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,0,0) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,0);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,0,0) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,0);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,0,0) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,0);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,0,0) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,0);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,0,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,0,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,0,0) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,0);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,0,0) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,0);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,0,2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,0,2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,0,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,0,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,0,2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,0,2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,0,2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,0,2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,0,2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,0,2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,0,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,0,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,0,2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,0,2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,0,2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,0,2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,0,2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,0,2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,0,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,0,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,0,2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,0,2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,0,2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,0,2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,2,-2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,-2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,2,-2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,-2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,2,-2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,-2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,2,-2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,-2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,2,-2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,-2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,2,-2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,-2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,2,-2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,-2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,2,-2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,-2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,2,-2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,-2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,2,-2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,-2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,2,-2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,-2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,2,-2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,-2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,2,-2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,-2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,2,-2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,-2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,2,0) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,0);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,2,0) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,0);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,2,0) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,0);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,2,0) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,0);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,2,0) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,0);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,2,0) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,0);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,2,0) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,0);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,2,0) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,0);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,2,0) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,0);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,2,0) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,0);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,2,0) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,0);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,2,0) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,0);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,2,0) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,0);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,2,0) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,0);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,2,2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,2,2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (1,2,2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(1,2,2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-1,2,2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-1,2,2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,2,2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,2,2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (5,2,2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(5,2,2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-5,2,2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-5,2,2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,2,2) + (0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,2);
    Vector3D ray_direction(0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,2,2) + (-0,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,2);
    Vector3D ray_direction(-0,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,2,2) + (1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,2);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,2,2) + (-1,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (10,2,2) + (10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(10,2,2);
    Vector3D ray_direction(10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Plane] No hit between YZ plane and (-10,2,2) + (-10,0,0) * t", "[Plane]")
{
    Point3D ray_origin(-10,2,2);
    Vector3D ray_direction(-10,0,0);

    auto primitive = raytracer::primitives::yz_plane();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

#endif
