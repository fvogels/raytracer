#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"

using namespace math;
using namespace raytracer::primitives;

TEST_CASE("[Intersection] Hits of Sphere(0,0,0) + Sphere(0,0,0) with (0,0,0)+(1,0,0)*t", "[Intersection]")
{
    auto s1 = sphere();
    auto s2 = sphere();
    Point3D ray_origin(0, 0, 0);
    Vector3D ray_direction(1, 0, 0);
    auto ray = Ray(ray_origin, ray_direction);

    auto i = intersection(s1, s2);

    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t == Approx(-1));
    REQUIRE(hits[1]->t == Approx(1));
}

TEST_CASE("[Intersection] Hits of Sphere(0,0,0) + Sphere(0,0,0) with (-2,0,0)+(1,0,0)*t", "[Intersection]")
{
    auto s1 = sphere();
    auto s2 = sphere();
    Point3D ray_origin(-2, 0, 0);
    Vector3D ray_direction(1, 0, 0);
    auto ray = Ray(ray_origin, ray_direction);

    auto i = intersection(s1, s2);

    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t == Approx(1));
    REQUIRE(hits[1]->t == Approx(3));
}

TEST_CASE("[Intersection] Hits of Sphere(0,0,0) + Sphere(1,0,0) with (-2,0,0)+(1,0,0)*t", "[Intersection]")
{
    auto s1 = sphere();
    auto s2 = translate(Vector3D(1, 0, 0), sphere());
    Point3D ray_origin(-2, 0, 0);
    Vector3D ray_direction(1, 0, 0);
    auto ray = Ray(ray_origin, ray_direction);

    auto i = intersection(s1, s2);

    auto hits = i->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
    REQUIRE(hits[0]->t == Approx(2));
    REQUIRE(hits[1]->t == Approx(3));
}

#endif
