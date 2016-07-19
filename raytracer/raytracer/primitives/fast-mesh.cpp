#include "primitives/fast-mesh.h"
#include "primitives/triangle.h"
#include "math/point3d.h"
#include "math/box.h"
#include "easylogging++.h"
#include <memory>
#include <stack>
#include <vector>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
#pragma pack(push, 1)

    struct XYZ
    {
        double x, y, z;
    };

    struct TRIANGLE
    {
        unsigned i, j, k;
        Vector3D n;
    };

    struct BOX
    {
        double min_x, max_x, min_y, max_y, min_z, max_z;
        unsigned i, j;
    };

#pragma pack(pop)

    class FastMesh : public _private_::PrimitiveImplementation
    {
    public:
        FastMesh(std::unique_ptr<XYZ[]> vertices, std::unique_ptr<TRIANGLE[]> triangles, std::unique_ptr<BOX[]> boxes, unsigned vertex_count, unsigned triangle_count, unsigned box_count)
            : m_vertices(std::move(vertices)), m_triangles(std::move(triangles)), m_boxes(std::move(boxes)), m_vertex_count(vertex_count), m_triangle_count(triangle_count), m_box_count(box_count) { }

        bool find_hit(const math::Ray& ray, Hit* hit) const override
        {
            return find_hit(ray, hit, 0x80000000 | (m_box_count - 1));
        }

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override
        {
            std::cerr << "Not supported (yet)" << std::endl;
            abort();
        }

        Box bounding_box() const override
        {
            return this->box(m_box_count - 1);
        }

    private:
        bool find_hit(const Ray& ray, Hit* hit, unsigned index) const
        {
            if (index & 0x80000000)
            {
                return find_box_hit(ray, hit, index & 0x7FFFFFFF);
            }
            else
            {
                return find_triangle_hit(ray, hit, index);
            }
        }

        bool find_box_hit(const Ray& ray, Hit* hit, unsigned index) const
        {
            const BOX& box = m_boxes[index];
            Box b = this->box(index);

            if (b.is_hit_positively_by(ray))
            {
                bool b1 = find_hit(ray, hit, box.i);
                bool b2 = find_hit(ray, hit, box.j);

                return b1 || b2;
            }
            else
            {
                return false;
            }
        }

        bool find_triangle_hit(const Ray& ray, Hit* hit, unsigned index) const
        {
            assert(index < m_triangle_count);

            const TRIANGLE& triangle = m_triangles[index];
            Point3D m_a = point(triangle.i);
            Point3D m_b = point(triangle.j);
            Point3D m_c = point(triangle.k);
            Vector3D m_normal = triangle.n;

            Vector3D normal = ray.direction.dot(m_normal) > 0 ? -m_normal : m_normal;
            double denom = m_normal.dot(ray.direction);

            if (denom == approx(0.0))
            {
                return false;
            }
            else
            {
                double numer = -(ray.origin - m_a).dot(normal);
                double t = numer / denom;

                if (0 < t && t < hit->t)
                {
                    const Point3D& A = m_a;
                    const Point3D& B = m_b;
                    const Point3D& C = m_c;
                    Point3D P = ray.at(t);

                    Vector3D AB = B - A;
                    Vector3D AC = C - A;
                    Vector3D AP = P - A;
                    Vector3D BC = C - B;
                    Vector3D BP = P - B;
                    Vector3D CA = A - C;
                    Vector3D CP = P - C;

                    Vector3D ABxAC = AB.cross(AC);
                    Vector3D ABxAP = AB.cross(AP);
                    Vector3D CAxCP = CA.cross(CP);
                    Vector3D BCxBP = BC.cross(BP);

                    double area_ABC = ABxAC.norm() / 2;
                    double area_ABP = ABxAP.norm() / 2;
                    double area_BCP = BCxBP.norm() / 2;

                    bool p_is_left_of_ab = ABxAP.dot(normal) > 0;
                    bool p_is_left_of_bc = BCxBP.dot(normal) > 0;
                    bool p_is_left_of_ca = CAxCP.dot(normal) > 0;

                    double gamma = area_ABP / area_ABC;
                    double beta = area_BCP / area_ABC;
                    double alpha = 1 - beta - gamma;

                    if (p_is_left_of_ab && p_is_left_of_bc && p_is_left_of_ca)
                    {
                        assert(alpha + beta + gamma == approx(1.0));
                        assert(0 <= alpha);
                        assert(0 <= beta);
                        assert(0 <= gamma);

                        hit->t = t;
                        hit->position = P;
                        hit->local_position.xyz = P;
                        hit->local_position.uv = Point2D(alpha, beta);
                        hit->normal = normal;

                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        }

        Point3D point(unsigned index) const
        {
            assert(index < m_vertex_count);

            return Point3D(m_vertices[index].x, m_vertices[index].y, m_vertices[index].z);
        }

        Vector3D vector(unsigned index) const
        {
            return Vector3D(m_vertices[index].x, m_vertices[index].y, m_vertices[index].z);
        }

        Box box(unsigned index) const
        {
            const BOX& box = m_boxes[index];
            Interval<double> x_interval(box.min_x, box.max_x);
            Interval<double> y_interval(box.min_y, box.max_y);
            Interval<double> z_interval(box.min_z, box.max_z);

            return Box(x_interval, y_interval, z_interval);
        }

        std::unique_ptr<XYZ[]> m_vertices;
        std::unique_ptr<TRIANGLE[]> m_triangles;
        std::unique_ptr<BOX[]> m_boxes;
        unsigned m_vertex_count, m_triangle_count, m_box_count;
    };

    Point3D to_point3d(XYZ xyz)
    {
        return Point3D(xyz.x, xyz.y, xyz.z);
    }

    Box construct_bounding_box(const XYZ* vertices, const TRIANGLE& triangle)
    {
        auto p = to_point3d(vertices[triangle.i]);
        auto q = to_point3d(vertices[triangle.j]);
        auto r = to_point3d(vertices[triangle.k]);

        Box b1 = Box::from_corners(p, q);
        Box b2 = Box::from_corners(p, r);

        return b1.merge(b2);
    }

    Box construct_bounding_box(const BOX& box)
    {
        auto x = Interval<double>::from_raw_bounds(box.min_x, box.max_x);
        auto y = Interval<double>::from_raw_bounds(box.min_y, box.max_y);
        auto z = Interval<double>::from_raw_bounds(box.min_z, box.max_z);

        return Box(x, y, z);
    }

    Primitive load_mesh_bbh(std::istream& in)
    {
        TIMED_FUNC(timerObj);
        CLOG(INFO, "mesh") << "Loading mesh...";

        unsigned n_vertices;
        in >> n_vertices;
        CLOG(INFO, "mesh") << "Reading " << n_vertices << " vertices";

        std::unique_ptr<XYZ[]> vertices(new XYZ[n_vertices]);

        for (unsigned i = 0; i != n_vertices; ++i)
        {
            double x, y, z;

            in >> x >> y >> z;

            vertices[i] = XYZ{ x, y, z };
        }

        CLOG(INFO, "mesh") << "Reading hierarchy";

        std::vector<TRIANGLE> triangles;
        std::vector<BOX> boxes;
        std::stack<unsigned> indices;

        while (true)
        {
            std::string tag;
            in >> tag;

            if (tag == "t")
            {
                unsigned i, j, k;

                in >> i >> j >> k;

                assert(i < n_vertices);
                assert(j < n_vertices);
                assert(k < n_vertices);

                Point3D p = to_point3d(vertices[i]);
                Point3D q = to_point3d(vertices[j]);
                Point3D r = to_point3d(vertices[k]);
                Vector3D n = (q - p).cross(r - p).normalized();

                assert(n.is_unit());

                TRIANGLE triangle;
                triangle.i = i;
                triangle.j = j;
                triangle.k = k;
                triangle.n = n;
                triangles.push_back(triangle);

                indices.push(unsigned(triangles.size()) - 1);
            }
            else if (tag == "g")
            {
                unsigned i = indices.top();
                indices.pop();
                unsigned j = indices.top();
                indices.pop();

                Box bounding_box = Box::empty();
                if (i & 0x80000000)
                {
                    // i is box index
                    unsigned index = i & 0x7FFFFFF;
                    assert(index < boxes.size());
                    const BOX& b = boxes[index];


                    bounding_box = bounding_box.merge(construct_bounding_box(b));
                }
                else
                {
                    // i is triangle index
                    assert(i < triangles.size());
                    const TRIANGLE& t = triangles[i];

                    bounding_box = bounding_box.merge(construct_bounding_box(vertices.get(), t));
                }

                if (j & 0x80000000)
                {
                    // j is box index
                    unsigned index = j & 0x7FFFFFFF;
                    assert(index < boxes.size());
                    const BOX& b = boxes[index];

                    bounding_box = bounding_box.merge(construct_bounding_box(b));
                }
                else
                {
                    // j is triangle index
                    assert(j < triangles.size());
                    const TRIANGLE& t = triangles[j];

                    bounding_box = bounding_box.merge(construct_bounding_box(vertices.get(), t));
                }

                BOX box;
                box.i = i;
                box.j = j;
                box.min_x = bounding_box.x().lower;
                box.max_x = bounding_box.x().upper;
                box.min_y = bounding_box.y().lower;
                box.max_y = bounding_box.y().upper;
                box.min_z = bounding_box.z().lower;
                box.max_z = bounding_box.z().upper;
                boxes.push_back(box);

                indices.push(0x80000000 | (unsigned(boxes.size()) - 1));
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

        assert(indices.size() == 1);

        std::unique_ptr<TRIANGLE[]> ts(new TRIANGLE[triangles.size()]);
        std::unique_ptr<BOX[]> bs(new BOX[boxes.size()]);

        for (unsigned i = 0; i != triangles.size(); ++i)
        {
            ts[i] = triangles[i];
        }

        for (unsigned i = 0; i != boxes.size(); ++i)
        {
            bs[i] = boxes[i];
        }

        return Primitive(std::make_shared<FastMesh>(std::move(vertices), std::move(ts), std::move(bs), unsigned(n_vertices), unsigned(triangles.size()), unsigned(boxes.size())));
    }

    template<typename T>
    T read(std::istream& in)
    {
        T result;

        in.read(reinterpret_cast<char*>(&result), sizeof(T));

        return result;
    }

    Primitive load_mesh_bbh_bin(std::istream& in)
    {
        TIMED_FUNC(timerObj);
        CLOG(INFO, "mesh") << "Loading mesh...";

        unsigned n_vertices = read<unsigned>(in);
        CLOG(INFO, "mesh") << "Reading " << n_vertices << " vertices";

        std::unique_ptr<XYZ[]> vertices(new XYZ[n_vertices]);

        for (unsigned i = 0; i != n_vertices; ++i)
        {
            double x = read<float>(in), y = read<float>(in), z = read<float>(in);

            vertices[i] = XYZ{ x, y, z };
        }

        CLOG(INFO, "mesh") << "Reading hierarchy";

        std::vector<TRIANGLE> triangles;
        std::vector<BOX> boxes;
        std::stack<unsigned> indices;

        unsigned tag;
        while ((tag = read<unsigned>(in)) != 0xFFFFFFFF)
        {
            switch (tag)
            {
            case 0x11111111:
            {
                unsigned i = read<unsigned>(in), j = read<unsigned>(in), k = read<unsigned>(in);

                assert(i < n_vertices);
                assert(j < n_vertices);
                assert(k < n_vertices);

                Point3D p = to_point3d(vertices[i]);
                Point3D q = to_point3d(vertices[j]);
                Point3D r = to_point3d(vertices[k]);
                Vector3D n = (q - p).cross(r - p).normalized();

                assert(n.is_unit());

                TRIANGLE triangle;
                triangle.i = i;
                triangle.j = j;
                triangle.k = k;
                triangle.n = n;
                triangles.push_back(triangle);

                indices.push(unsigned(triangles.size()) - 1);
                break;
            }
            case 0x22222222:
            {
                unsigned i = indices.top();
                indices.pop();
                unsigned j = indices.top();
                indices.pop();

                Box bounding_box = Box::empty();
                if (i & 0x80000000)
                {
                    // i is box index
                    unsigned index = i & 0x7FFFFFF;
                    assert(index < boxes.size());
                    const BOX& b = boxes[index];


                    bounding_box = bounding_box.merge(construct_bounding_box(b));
                }
                else
                {
                    // i is triangle index
                    assert(i < triangles.size());
                    const TRIANGLE& t = triangles[i];

                    bounding_box = bounding_box.merge(construct_bounding_box(vertices.get(), t));
                }

                if (j & 0x80000000)
                {
                    // j is box index
                    unsigned index = j & 0x7FFFFFFF;
                    assert(index < boxes.size());
                    const BOX& b = boxes[index];

                    bounding_box = bounding_box.merge(construct_bounding_box(b));
                }
                else
                {
                    // j is triangle index
                    assert(j < triangles.size());
                    const TRIANGLE& t = triangles[j];

                    bounding_box = bounding_box.merge(construct_bounding_box(vertices.get(), t));
                }

                BOX box;
                box.i = i;
                box.j = j;
                box.min_x = bounding_box.x().lower;
                box.max_x = bounding_box.x().upper;
                box.min_y = bounding_box.y().lower;
                box.max_y = bounding_box.y().upper;
                box.min_z = bounding_box.z().lower;
                box.max_z = bounding_box.z().upper;
                boxes.push_back(box);

                indices.push(0x80000000 | (unsigned(boxes.size()) - 1));
                break;
            }

            default:
                std::cerr << "Unrecognized tag " << tag << std::endl;
                abort();
            }
        }

        assert(indices.size() == 1);

        std::unique_ptr<TRIANGLE[]> ts(new TRIANGLE[triangles.size()]);
        std::unique_ptr<BOX[]> bs(new BOX[boxes.size()]);

        for (unsigned i = 0; i != triangles.size(); ++i)
        {
            ts[i] = triangles[i];
        }

        for (unsigned i = 0; i != boxes.size(); ++i)
        {
            bs[i] = boxes[i];
        }

        return Primitive(std::make_shared<FastMesh>(std::move(vertices), std::move(ts), std::move(bs), unsigned(n_vertices), unsigned(triangles.size()), unsigned(boxes.size())));
    }
}

Primitive raytracer::primitives::fast_mesh(std::istream& in)
{
    std::string tag;
    in >> tag;

    if (tag == "raw")
    {
        std::cerr << "raw not supported" << std::endl;
        abort();
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

Primitive raytracer::primitives::fast_mesh_bin(std::istream& in)
{
    unsigned tag = read<unsigned>(in);

    switch (tag)
    {
    case 12345:
        return load_mesh_bbh_bin(in);

    default:
        std::cerr << "Unrecognized mesh tag " << tag << std::endl;
        abort();
    }
}