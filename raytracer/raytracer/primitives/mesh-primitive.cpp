#include "primitives/mesh-primitive.h"
#include "primitives/triangle-primitive.h"
#include "primitives/bounding-box-accelerator-primitive.h"
#include "primitives/union-primitive.h"
#include "easylogging++.h"
#include "util/misc.h"
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

    Primitive load_mesh_from_stream(std::istream& in)
    {
        TIMED_FUNC(timerObj);
        LOG(INFO) << "Loading mesh (unoptimized version)...";

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

        LOG(INFO) << "Read " << vertices.size() << " vertices";
        LOG(INFO) << "Reading hierarchy";

        std::vector<Primitive> primitives;
        unsigned triangle_count = 0;
        unsigned box_count = 0;

        while (true)
        {
            std::string tag;
            in >> tag;

            if (tag == "t")
            {
                unsigned i, j, k;

                in >> i >> j >> k;
                primitives.push_back(triangle(vertices[i], vertices[j], vertices[k]));

                triangle_count++;
            }
            else if (tag == "b")
            {
                unsigned n;
                in >> n;

                std::vector<Primitive> children;

                for (unsigned i = 0; i != n; ++i)
                {
                    children.push_back(primitives.back());
                    primitives.pop_back();
                }

                // primitives.push_back(accelerated_union(children));
                primitives.push_back(bounding_box_accelerator(make_union(children)));

                box_count++;
            }
            else if (tag == "end")
            {
                break;
            }
            else
            {
                LOG(ERROR) << "Unrecognized tag \"" << tag << "\"" << std::endl;
                abort();
            }
        }

        assert(primitives.size() == 1);
        LOG(INFO) << "Mesh counted " << triangle_count << " triangles and " << box_count << " boxes";

        return primitives[0];
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

Primitive raytracer::primitives::load_mesh(const std::string& path)
{
    std::ifstream in(path);
    CHECK(in) << "Failed to open " << path;

    return load_mesh_from_stream(in);
}
