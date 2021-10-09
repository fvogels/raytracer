#include "primitives/mesh/mesh-primitive.h"
#include "primitives/mesh/mesh-text-reader.h"
#include "primitives/mesh/mesh-binary-reader.h"
#include "primitives/primitives.h"
#include "util/misc.h"
#include <vector>
#include <stack>
#include "easylogging++.h"


using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class Receiver : public MeshReceiver
    {
    private:
        std::vector<Point3D> m_vertices;
        std::stack<Primitive> m_stack;
        unsigned m_triangle_count;
        unsigned m_box_count;

    public:
        Receiver()
            : m_triangle_count(0)
        {
            // NOP
        }

        virtual void vertex(double x, double y, double z)
        {
            Point3D vertex(x, y, z);
            m_vertices.push_back(vertex);
        }

        virtual void normal(double, double, double)
        {
            LOG(ERROR) << "Normals not supported";
            abort();
        }

        virtual void triangle(unsigned vertex1, unsigned vertex2, unsigned vertex3)
        {
            const auto& v1 = m_vertices[vertex1];
            const auto& v2 = m_vertices[vertex2];
            const auto& v3 = m_vertices[vertex3];
            auto triangle = raytracer::primitives::triangle(v1, v2, v3);

            m_stack.push(triangle);
            ++m_triangle_count;
        }

        virtual void box(unsigned n_children)
        {
            std::vector<Primitive> children;

            for (unsigned i = 0; i != n_children; ++i)
            {
                CHECK(!m_stack.empty()) << "Stack is empty";

                children.push_back(m_stack.top());
                m_stack.pop();
            }

            auto children_union = make_union(children);
            auto box = raytracer::primitives::bounding_box_accelerator(children_union);

            m_stack.push(box);
            m_box_count++;
        }

        Primitive root() const
        {
            CHECK(m_stack.size() == 1) << "Multiple children in stack";

            return m_stack.top();
        }

        unsigned triangle_count() const
        {
            return m_triangle_count;
        }

        unsigned box_count() const
        {
            return m_box_count;
        }
    };
}


Primitive raytracer::primitives::mesh(const std::string& path)
{
    if (ends_with(path, ".bmesh"))
    {
        std::ifstream input_stream(path, std::ios::binary);
        CHECK(input_stream) << "Could not open " << path;
        Receiver receiver;

        read_binary_mesh(input_stream, receiver);

        LOG(INFO) << "Mesh contained " << receiver.triangle_count() << " triangles and " << receiver.box_count() << " boxes";

        return receiver.root();
    }
    else
    {
        std::ifstream input_stream(path);
        CHECK(input_stream) << "Could not open " << path;
        Receiver receiver;

        read_text_mesh(input_stream, receiver);

        LOG(INFO) << "Mesh contained " << receiver.triangle_count() << " triangles and " << receiver.box_count() << " boxes";

        return receiver.root();        
    }
}
