#ifdef TEST_BUILD

#include "Catch.h"
#include "materials/materials.h"
#include "primitives/plane.h"
#include "math/vector3d.h"
#include "math/point3d.h"

using namespace raytracer;
using namespace math;


TEST_CASE("[Plane] Hitting plane with N=(0,0,1), P=(0,0,0) with ray=(0,0,5)+(0,0,-1)t", "[Plane]")
{
	Point3D p(0, 0, 0);
	Vector3D n(0, 0, 1);
	Vector3D u(1, 0, 0);
	Point3D o(0, 0, 5);
	Vector3D d(0, 0, -1);

	Plane plane(p, n, u);
	Ray ray(o, d);
	Hit hit;
	hit.material = raytracer::materials::uniform(colors::black());
	
	REQUIRE(plane.find_hit(ray, &hit));
}

#endif
