#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[Sphere] No hit with ray (0,0,5) + (0,0,1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,5);
    Vector3D ray_direction(0,0,1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 10;

    REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Sphere] No hit with ray (0,0,-5) + (0,0,-1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,-5);
    Vector3D ray_direction(0,0,-1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 10;

    REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Sphere] No hit with ray (0,2,0) + (0,1,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,2,0);
    Vector3D ray_direction(0,1,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 10;

    REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Sphere] No hit with ray (0,-2,0) + (0,-1,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,-2,0);
    Vector3D ray_direction(0,-1,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 10;

    REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Sphere] No hit with ray (4,0,0) + (1,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(4,0,0);
    Vector3D ray_direction(1,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 10;

    REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Sphere] No hit with ray (-4,0,0) + (-1,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(-4,0,0);
    Vector3D ray_direction(-1,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 10;

    REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Sphere] No hit with ray (4,0,0) + (-1,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(4,0,0);
    Vector3D ray_direction(-1,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 2;

    REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Sphere] No hit with ray (40,0,0) + (-1,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(40,0,0);
    Vector3D ray_direction(-1,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 10;

    REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Sphere] No hit with ray (40,0,0) + (-2,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(40,0,0);
    Vector3D ray_direction(-2,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;
    hit.t = 10;

    REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
}

TEST_CASE("[Sphere] First hit with ray (0,0,5) + (0,0,-1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,5);
    Vector3D ray_direction(0,0,-1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(sphere->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(4));
    CHECK(hit.position == approx(Point3D(0,0,1)));
    CHECK(hit.normal == approx(Vector3D(0,0,1)));
}

TEST_CASE("[Sphere] First hit with ray (0,0,3) + (0,0,-1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,3);
    Vector3D ray_direction(0,0,-1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(sphere->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(2));
    CHECK(hit.position == approx(Point3D(0,0,1)));
    CHECK(hit.normal == approx(Vector3D(0,0,1)));
}

TEST_CASE("[Sphere] First hit with ray (0,0,-3) + (0,0,+1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,-3);
    Vector3D ray_direction(0,0,+1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(sphere->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(2));
    CHECK(hit.position == approx(Point3D(0,0,-1)));
    CHECK(hit.normal == approx(Vector3D(0,0,-1)));
}

TEST_CASE("[Sphere] First hit with ray (4,0,0) + (-1,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(4,0,0);
    Vector3D ray_direction(-1,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(sphere->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(3));
    CHECK(hit.position == approx(Point3D(1,0,0)));
    CHECK(hit.normal == approx(Vector3D(1,0,0)));
}

TEST_CASE("[Sphere] First hit with ray (-8,0,0) + (1,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(-8,0,0);
    Vector3D ray_direction(1,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(sphere->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(7));
    CHECK(hit.position == approx(Point3D(-1,0,0)));
    CHECK(hit.normal == approx(Vector3D(-1,0,0)));
}

TEST_CASE("[Sphere] First hit with ray (0,4,0) + (0,-1,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,4,0);
    Vector3D ray_direction(0,-1,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(sphere->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(3));
    CHECK(hit.position == approx(Point3D(0,1,0)));
    CHECK(hit.normal == approx(Vector3D(0,1,0)));
}

TEST_CASE("[Sphere] First hit with ray (0,-2,0) + (0,1,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,-2,0);
    Vector3D ray_direction(0,1,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(sphere->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,-1,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0)));
}

TEST_CASE("[Sphere] First hit with ray (0,0,0) + (0,1,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,0);
    Vector3D ray_direction(0,1,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    REQUIRE(sphere->find_first_positive_hit(ray, &hit));
    CHECK(hit.t == Approx(1));
    CHECK(hit.position == approx(Point3D(0,1,0)));
    CHECK(hit.normal == approx(Vector3D(0,-1,0)));
}

TEST_CASE("[Sphere] All hits with ray (0,0,5) + (0,0,-1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,5);
    Vector3D ray_direction(0,0,-1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == 4);
    CHECK(hits[1]->t == 6);
}

TEST_CASE("[Sphere] All hits with ray (0,0,4) + (0,0,-1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,4);
    Vector3D ray_direction(0,0,-1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == 3);
    CHECK(hits[1]->t == 5);
}

TEST_CASE("[Sphere] All hits with ray (0,0,-5) + (0,0,1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,-5);
    Vector3D ray_direction(0,0,1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == 4);
    CHECK(hits[1]->t == 6);
}

TEST_CASE("[Sphere] All hits with ray (0,0,-3) + (0,0,1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,-3);
    Vector3D ray_direction(0,0,1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == 2);
    CHECK(hits[1]->t == 4);
}

TEST_CASE("[Sphere] All hits with ray (3,0,0) + (-1,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(3,0,0);
    Vector3D ray_direction(-1,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == 2);
    CHECK(hits[1]->t == 4);
}

TEST_CASE("[Sphere] All hits with ray (-3,0,0) + (1,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(-3,0,0);
    Vector3D ray_direction(1,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == 2);
    CHECK(hits[1]->t == 4);
}

TEST_CASE("[Sphere] All hits with ray (0,7,0) + (0,-1,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,7,0);
    Vector3D ray_direction(0,-1,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == 6);
    CHECK(hits[1]->t == 8);
}

TEST_CASE("[Sphere] All hits with ray (0,-7,0) + (0,1,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,-7,0);
    Vector3D ray_direction(0,1,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == 6);
    CHECK(hits[1]->t == 8);
}

TEST_CASE("[Sphere] All hits with ray (0,-7,0) + (0,2,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,-7,0);
    Vector3D ray_direction(0,2,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == 3);
    CHECK(hits[1]->t == 4);
}

TEST_CASE("[Sphere] All hits with ray (0,0,0) + (0,1,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,0);
    Vector3D ray_direction(0,1,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == -1);
    CHECK(hits[1]->t == 1);
}

TEST_CASE("[Sphere] All hits with ray (0,0,0) + (0,0,1) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,0);
    Vector3D ray_direction(0,0,1);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == -1);
    CHECK(hits[1]->t == 1);
}

TEST_CASE("[Sphere] All hits with ray (0,0,0) + (1,0,0) * t", "[Sphere]")
{
    Point3D ray_origin(0,0,0);
    Vector3D ray_direction(1,0,0);

    auto sphere = raytracer::primitives::sphere();
    Ray ray(ray_origin, ray_direction);

    Hit hit;

    auto hits = sphere->find_all_hits(ray);
    REQUIRE(hits.size() == 2);
    CHECK(hits[0]->t == -1);
    CHECK(hits[1]->t == 1);
}

#endif
