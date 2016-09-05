#include "primitives/mesh-primitive.h"
#include "primitives/triangle-primitive.h"
#include "primitives/bounding-box-accelerator-primitive.h"
#include "primitives/union-primitive.h"
#include "easylogging++.h"
#include <vector>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


namespace
{
    class MeshImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        MeshImplementation(const std::vector<Primitive>& children)
            : m_children(children)
        {
            // NOP
        }

        MeshImplementation(std::vector<Primitive>&& children)
            : m_children(children)
        {
            // NOP
        }

        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            bool found_hit = false;

            for (const auto& child : this->m_children)
            {
                found_hit = child->find_first_positive_hit(ray, hit) || found_hit;
            }

            return found_hit;
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> hits;

            for (const auto& child : this->m_children)
            {
                for (auto hit : child->find_all_hits(ray))
                {
                    hits.push_back(hit);
                }
            }

            std::sort(hits.begin(), hits.end(), [](const std::shared_ptr<Hit>& h1, const std::shared_ptr<Hit>& h2)
            {
                return h1->t < h2->t;
            });

            return hits;
        }

        math::Box bounding_box() const override
        {
            Box result = Box::empty();

            for (auto child : this->m_children)
            {
                Box child_box = child->bounding_box();
                result = result.merge(child_box);
            }

            return result;
        }

    private:
        std::vector<Primitive> m_children;
    };

    Primitive load_mesh_raw(std::istream& in)
    {
        TIMED_FUNC(timerObj);
        LOG(INFO) << "Loading mesh...";

        unsigned n_vertices;
        in >> n_vertices;
        LOG(INFO) << "Reading " << n_vertices << " vertices";

        std::vector<Point3D> vertices;

        for (unsigned i = 0; i != n_vertices; ++i)
        {
            double x, y, z;

            in >> x >> y >> z;

            vertices.push_back(Point3D(x, y, z));
        }

        unsigned n_triangles;
        in >> n_triangles;

        LOG(INFO) << "Reading " << n_triangles << " triangles";

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

        LOG(INFO) << "Building optimized hierarchy...";
        return accelerated_union(triangles);
    }

    Primitive load_mesh_bbh(std::istream& in)
    {
        TIMED_FUNC(timerObj);
        LOG(INFO) << "Loading mesh...";

        unsigned n_vertices;
        in >> n_vertices;
        LOG(INFO) << "Reading " << n_vertices << " vertices";

        std::vector<Point3D> vertices;

        for (unsigned i = 0; i != n_vertices; ++i)
        {
            double x, y, z;

            in >> x >> y >> z;

            vertices.push_back(Point3D(x, y, z));
        }

        LOG(INFO) << "Reading hierarchy";

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
                LOG(ERROR) << "Unrecognized tag " << tag << std::endl;
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
        LOG(ERROR) << "Unrecognized mesh tag " << tag << std::endl;
        abort();
    }
}

Primitive raytracer::primitives::mesh(const std::vector<Primitive>& children)
{
    return Primitive(std::make_shared<MeshImplementation>(children));
}

Primitive raytracer::primitives::mesh(std::vector<Primitive>&& children)
{
    return Primitive(std::make_shared<MeshImplementation>(children));
}
