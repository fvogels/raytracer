#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/cone.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[Cone] First hit (-15,0,10)+(1,0,0)*t with Z-cone", "[Cone]")
{
    auto c = cone_along_z();
    Ray ray(Point3D(-15, 0, 10), Vector3D(1, 0, 0));
    Hit hit;

    REQUIRE(c->find_hit(ray, &hit));
    REQUIRE(hit.t == Approx(5));
    REQUIRE(hit.normal == approx(Vector3D(-1,0,-1).normalized()));
}

TEST_CASE("[Cone] First hit (-11,0,10)+(1,0,0)*t with Z-cone", "[Cone]")
{
    auto c = cone_along_z();
    Ray ray(Point3D(-11, 0, 10), Vector3D(1, 0, 0));
    Hit hit;

    REQUIRE(c->find_hit(ray, &hit));
    REQUIRE(hit.t == Approx(1));
    REQUIRE(hit.normal == approx(Vector3D(-1, 0, -1).normalized()));
}

TEST_CASE("[Cone] First hit (11,0,10)+(-1,0,0)*t with Z-cone", "[Cone]")
{
    auto c = cone_along_z();
    Ray ray(Point3D(11, 0, 10), Vector3D(-1, 0, 0));
    Hit hit;

    REQUIRE(c->find_hit(ray, &hit));
    REQUIRE(hit.t == Approx(1));
    REQUIRE(hit.normal == approx(Vector3D(1, 0, -1).normalized()));
}

#endif
