#include "primitives/mesh.h"
#include "primitives/triangle.h"
#include "primitives/bounding-box-accelerator.h"
#include "primitives/union.h"
#include "easylogging++.h"
#include <vector>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


namespace
{
    Primitive load_mesh_raw(std::istream& in)
    {
        TIMED_FUNC(timerObj);
        CLOG(INFO, "mesh") << "Loading mesh...";

        unsigned n_vertices;
        in >> n_vertices;
        CLOG(INFO, "mesh") << "Reading " << n_vertices << " vertices";

        std::vector<Point3D> vertices;

        for (unsigned i = 0; i != n_vertices; ++i)
        {
            double x, y, z;

            in >> x >> y >> z;

            vertices.push_back(point(x, y, z));
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

    Primitive load_mesh_bbh(std::istream& in)
    {
        TIMED_FUNC(timerObj);
        CLOG(INFO, "mesh") << "Loading mesh...";

        unsigned n_vertices;
        in >> n_vertices;
        CLOG(INFO, "mesh") << "Reading " << n_vertices << " vertices";

        std::vector<Point3D> vertices;

        for (unsigned i = 0; i != n_vertices; ++i)
        {
            double x, y, z;

            in >> x >> y >> z;

            vertices.push_back(point(x, y, z));
        }

        CLOG(INFO, "mesh") << "Reading hierarchy";

        std::vector<Primitive> primitives;

        while (true)
        {
            std::string tag;
            in >> tag;

            if (tag == "t")
            {
                unsigned i, j, k;

                in >> i >> j >> k;
                primitives.push_back(triangle(vertices[i], vertices[j], vertices[k]));
            }
            else if (tag == "g")
            {
                unsigned n = 2;

                std::vector<Primitive> children;

                for (unsigned i = 0; i != n; ++i)
                {
                    children.push_back(primitives.back());
                    primitives.pop_back();
                }

                primitives.push_back(accelerated_union(children));
            }
            else if (tag == "end")
            {
                break;
            }
            else
            {
                std::cerr << "Unrecognized tag " << tag << std::endl;
                abort();
            }
        }

        assert(primitives.size() == 1);

        return primitives[0];
    }
}

Primitive raytracer::primitives::load_mesh(std::istream& in)
{
    std::string tag;
    in >> tag;

    if (tag == "raw")
    {
        return load_mesh_raw(in);
    }
    else if (tag == "bbh")
    {
        return load_mesh_bbh(in);
    }
    else
    {
        std::cerr << "Unrecognized mesh tag " << tag << std::endl;
        abort();
    }
}