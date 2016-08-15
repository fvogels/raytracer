#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"

using namespace math;
using namespace raytracer::primitives;


TEST_CASE("[Intersection] Hits of Sphere(0,0,0) + Sphere(0,0,0) with (10,0,0)+(-1,0,0)*t", "[Intersection]")
{
    auto s1 = translate(Vector3D(0,0,0), sphere());
    auto s2 = translate(Vector3D(0,0,0), sphere());
    Point3D ray_origin(10,0,0);
    Vector3D ray_direction(-1,0,0);
    auto ray = Ray(ray_origin, ray_direction);
    auto i = intersection(s1, s2);
    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t == Approx(9));
    REQUIRE(hits[1]->t == Approx(11));
}

TEST_CASE("[Intersection] Hits of Sphere(0,0,0) + Sphere(0,0,0) with (5,0,0)+(-1,0,0)*t", "[Intersection]")
{
    auto s1 = translate(Vector3D(0,0,0), sphere());
    auto s2 = translate(Vector3D(0,0,0), sphere());
    Point3D ray_origin(5,0,0);
    Vector3D ray_direction(-1,0,0);
    auto ray = Ray(ray_origin, ray_direction);
    auto i = intersection(s1, s2);
    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t == Approx(4));
    REQUIRE(hits[1]->t == Approx(6));
}

TEST_CASE("[Intersection] Hits of Sphere(-0.5,0,0) + Sphere(0.5,0,0) with (5,0,0)+(-1,0,0)*t", "[Intersection]")
{
    auto s1 = translate(Vector3D(-0.5,0,0), sphere());
    auto s2 = translate(Vector3D(0.5,0,0), sphere());
    Point3D ray_origin(5,0,0);
    Vector3D ray_direction(-1,0,0);
    auto ray = Ray(ray_origin, ray_direction);
    auto i = intersection(s1, s2);
    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t == Approx(4.5));
    REQUIRE(hits[1]->t == Approx(5.5));
}

TEST_CASE("[Intersection] Hits of Sphere(-0.25,0,0) + Sphere(0.25,0,0) with (5,0,0)+(-1,0,0)*t", "[Intersection]")
{
    auto s1 = translate(Vector3D(-0.25,0,0), sphere());
    auto s2 = translate(Vector3D(0.25,0,0), sphere());
    Point3D ray_origin(5,0,0);
    Vector3D ray_direction(-1,0,0);
    auto ray = Ray(ray_origin, ray_direction);
    auto i = intersection(s1, s2);
    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t == Approx(4.25));
    REQUIRE(hits[1]->t == Approx(5.75));
}

TEST_CASE("[Intersection] No hits Sphere(0,0,0) + Sphere(0,0,0) with (10,10,0)+(-1,0,0)*t", "[Intersection]")
{
    auto s1 = translate(Vector3D(0,0,0), sphere());
    auto s2 = translate(Vector3D(0,0,0), sphere());
    Point3D ray_origin(10,10,0);
    Vector3D ray_direction(-1,0,0);
    auto ray = Ray(ray_origin, ray_direction);
    auto i = intersection(s1, s2);
    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 0);
}

TEST_CASE("[Intersection] No hits Sphere(-2,0,0) + Sphere(2,0,0) with (10,0,0)+(-1,0,0)*t", "[Intersection]")
{
    auto s1 = translate(Vector3D(-2,0,0), sphere());
    auto s2 = translate(Vector3D(2,0,0), sphere());
    Point3D ray_origin(10,0,0);
    Vector3D ray_direction(-1,0,0);
    auto ray = Ray(ray_origin, ray_direction);
    auto i = intersection(s1, s2);
    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 0);
}

TEST_CASE("[Intersection] No hits Sphere(0,2,0) + Sphere(0,-2,0) with (10,0,0)+(-1,0,0)*t", "[Intersection]")
{
    auto s1 = translate(Vector3D(0,2,0), sphere());
    auto s2 = translate(Vector3D(0,-2,0), sphere());
    Point3D ray_origin(10,0,0);
    Vector3D ray_direction(-1,0,0);
    auto ray = Ray(ray_origin, ray_direction);
    auto i = intersection(s1, s2);
    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 0);
}

#endif
