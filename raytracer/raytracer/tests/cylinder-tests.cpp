#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[Cylinder] First hit (-5,0,0)+(1,0,0)*t with Z-cylinder", "[Cylinder]")
{
    auto c = cylinder();
    Ray ray(Point3D(-5, 0, 0), Vector3D(1, 0, 0));
    Hit hit;

    REQUIRE(c->find_hit(ray, &hit));
    REQUIRE(hit.t == Approx(4));
    REQUIRE(hit.normal == approx<Vector3D>(Vector3D(-1, 0, 0)));
}

TEST_CASE("[Cylinder] First hit (5,0,0)+(1,0,0)*t with Z-cylinder", "[Cylinder]")
{
    auto c = cylinder();
    Ray ray(Point3D(5, 0, 0), Vector3D(1, 0, 0));
    Hit hit;

    REQUIRE(!c->find_hit(ray, &hit));
}

TEST_CASE("[Cylinder] First hit (5,0,0)+(-1,0,0)*t with Z-cylinder", "[Cylinder]")
{
    auto c = cylinder();
    Ray ray(Point3D(5, 0, 0), Vector3D(-1, 0, 0));
    Hit hit;

    REQUIRE(c->find_hit(ray, &hit));
    REQUIRE(hit.t == Approx(4));
    REQUIRE(hit.normal == approx<Vector3D>(Vector3D(1, 0, 0)));
}

#endif
