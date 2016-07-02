#include "primitives/mesh.h"
#include "primitives/triangle.h"
#include "primitives/bounding-box-accelerator.h"
#include "easylogging++.h"
#include <vector>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


Primitive raytracer::primitives::load_mesh(std::istream& in)
{   
    CLOG(INFO, "mesh") << "Loading mesh...";
    unsigned n_vertices;
    in >> n_vertices;
    CLOG(INFO, "mesh") << "Reading " << n_vertices << " vertices";

    std::vector<Point3D> vertices;

    for (unsigned i = 0; i != n_vertices; ++i)
    {
        double x, y, z;

        in >> x >> y >> z;

        vertices.push_back(Point3D(x, y, z));
    }

    unsigned n_triangles;
    in >> n_triangles;

    CLOG(INFO, "mesh") << "Reading " << n_triangles << " triangles";

    std::vector<Primitive> triangles;

    for (unsigned i = 0; i != n_triangles; ++i)
    {
        unsigned a, b, c;

        in >> a >> b >> c;

        assert(a < vertices.size());
        assert(b < vertices.size());
        assert(c < vertices.size());

        Point3D p = vertices[a];
        Point3D q = vertices[b];
        Point3D r = vertices[c];

        Primitive primitive = triangle(p, q, r);

        triangles.push_back(primitive);
    }

    CLOG(INFO, "mesh") << "Building optimized hierarchy...";
    return accelerated_union(triangles);
}