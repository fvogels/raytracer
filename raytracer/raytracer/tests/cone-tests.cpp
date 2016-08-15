#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[Cone] Hit between cone along z and (10,0,1) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(10,0,1);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(9));
    CHECK(hit.position == approx(Point3D(1,0,1)));
    CHECK(hit.normal == approx(Vector3D(1,0,-1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (-10,0,1) + (1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(-10,0,1);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(9));
    CHECK(hit.position == approx(Point3D(-1,0,1)));
    CHECK(hit.normal == approx(Vector3D(-1,0,-1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (7,0,1) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(7,0,1);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(6));
    CHECK(hit.position == approx(Point3D(1,0,1)));
    CHECK(hit.normal == approx(Vector3D(1,0,-1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (7,0,2) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(7,0,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(5));
    CHECK(hit.position == approx(Point3D(2,0,2)));
    CHECK(hit.normal == approx(Vector3D(1,0,-1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (7,0,3) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(7,0,3);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(4));
    CHECK(hit.position == approx(Point3D(3,0,3)));
    CHECK(hit.normal == approx(Vector3D(1,0,-1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (0,5,3) + (0,-1,0) * t", "[Cone]")
{
    Point3D ray_origin(0,5,3);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(2));
    CHECK(hit.position == approx(Point3D(0,3,3)));
    CHECK(hit.normal == approx(Vector3D(0,1,-1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (0,7,3) + (0,-2,0) * t", "[Cone]")
{
    Point3D ray_origin(0,7,3);
    Vector3D ray_direction(0,-2,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(2));
    CHECK(hit.position == approx(Point3D(0,3,3)));
    CHECK(hit.normal == approx(Vector3D(0,1,-1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (0,7,1) + (0,-2,0) * t", "[Cone]")
{
    Point3D ray_origin(0,7,1);
    Vector3D ray_direction(0,-2,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(3));
    CHECK(hit.position == approx(Point3D(0,1,1)));
    CHECK(hit.normal == approx(Vector3D(0,1,-1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (0,-7,1) + (0,2,0) * t", "[Cone]")
{
    Point3D ray_origin(0,-7,1);
    Vector3D ray_direction(0,2,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(3));
    CHECK(hit.position == approx(Point3D(0,-1,1)));
    CHECK(hit.normal == approx(Vector3D(0,-1,-1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (0,-7,-1) + (0,2,0) * t", "[Cone]")
{
    Point3D ray_origin(0,-7,-1);
    Vector3D ray_direction(0,2,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(3));
    CHECK(hit.position == approx(Point3D(0,-1,-1)));
    CHECK(hit.normal == approx(Vector3D(0,-1,1).normalized()));
}

TEST_CASE("[Cone] Hit between cone along z and (0,0,1) + (0,1,0) * t", "[Cone]")
{
    Point3D ray_origin(0,0,1);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(primitive->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,1,1)));
    CHECK(hit.normal == approx(Vector3D(0,-1,1).normalized()));
}

TEST_CASE("[Cone] No hit between cone along z and (10,0,1) + (1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(10,0,1);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 100;

    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Cone] No hit between cone along z and (2,0,1) + (1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(2,0,1);
    Vector3D ray_direction(1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 100;

    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Cone] No hit between cone along z and (-2,0,1) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(-2,0,1);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 100;

    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Cone] No hit between cone along z and (0,2,1) + (0,1,0) * t", "[Cone]")
{
    Point3D ray_origin(0,2,1);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 100;

    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Cone] No hit between cone along z and (0,5,4) + (0,1,0) * t", "[Cone]")
{
    Point3D ray_origin(0,5,4);
    Vector3D ray_direction(0,1,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 100;

    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Cone] No hit between cone along z and (0,-5,4) + (0,-1,0) * t", "[Cone]")
{
    Point3D ray_origin(0,-5,4);
    Vector3D ray_direction(0,-1,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 100;

    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Cone] No hit between cone along z and (0,0,1) + (0,0,1) * t", "[Cone]")
{
    Point3D ray_origin(0,0,1);
    Vector3D ray_direction(0,0,1);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 100;

    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Cone] No hit between cone along z and (10,0,1) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(10,0,1);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 5;

    REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Cone] All hits between cone along z and (5,0,1) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(5,0,1);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);
    auto hits = primitive->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t <= hits[1]->t);
    CHECK(hits[0]->t == Approx(4));
    CHECK(hits[1]->t == Approx(6));
}

TEST_CASE("[Cone] All hits between cone along z and (6,0,1) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(6,0,1);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);
    auto hits = primitive->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t <= hits[1]->t);
    CHECK(hits[0]->t == Approx(5));
    CHECK(hits[1]->t == Approx(7));
}

TEST_CASE("[Cone] All hits between cone along z and (6,0,2) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(6,0,2);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);
    auto hits = primitive->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t <= hits[1]->t);
    CHECK(hits[0]->t == Approx(4));
    CHECK(hits[1]->t == Approx(8));
}

TEST_CASE("[Cone] All hits between cone along z and (6,0,3) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(6,0,3);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);
    auto hits = primitive->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t <= hits[1]->t);
    CHECK(hits[0]->t == Approx(3));
    CHECK(hits[1]->t == Approx(9));
}

TEST_CASE("[Cone] All hits between cone along z and (7,0,3) + (-1,0,0) * t", "[Cone]")
{
    Point3D ray_origin(7,0,3);
    Vector3D ray_direction(-1,0,0);

    auto primitive = raytracer::primitives::cone_along_z();
    Ray ray(ray_origin, ray_direction);
    auto hits = primitive->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t <= hits[1]->t);
    CHECK(hits[0]->t == Approx(4));
    CHECK(hits[1]->t == Approx(10));
}

#endif
