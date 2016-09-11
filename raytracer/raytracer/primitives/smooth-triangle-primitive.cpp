#include "primitives/smooth-triangle-primitive.h"
#include "math/misc.h"
#include "easylogging++.h"
#include <assert.h>
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


namespace
{
    class SmoothTriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        SmoothTriangleImplementation(const Point3D& a, const Point3D& b, const Point3D& c, const Vector3D& na, const Vector3D& nb, const Vector3D& nc)
            : m_a(a), m_b(b), m_c(c), m_na(na), m_nb(nb), m_nc(nc)
        {
            assert(m_na.is_unit());
            assert(m_nb.is_unit());
            assert(m_nc.is_unit());

            m_normal = (b - a).cross(c - a).normalized();
        }

        bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
        {
            if (ray.direction.dot(m_normal) > 0)
            {
                return false;
            }
            else
            {
                const Vector3D& normal = m_normal;
                double denom = normal.dot(ray.direction);

                if (denom == approx(0.0))
                {
                    return false;
                }
                else
                {
                    double numer = (m_a - ray.origin).dot(normal);
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
                        double alpha = area_BCP / area_ABC;
                        double beta = 1 - alpha - gamma;

                        if (p_is_left_of_ab && p_is_left_of_bc && p_is_left_of_ca)
                        {
                            assert(alpha + beta + gamma == approx(1.0));
                            assert(alpha * (A - Point3D(0, 0, 0)) + beta * (B - Point3D(0, 0, 0)) + gamma * (C - Point3D(0, 0, 0)) == approx(P - Point3D(0, 0, 0)));
                            assert(0 <= alpha);
                            assert(0 <= beta);
                            assert(0 <= gamma);

                            hit->t = t;
                            hit->position = P;
                            hit->local_position.xyz = P;
                            hit->local_position.uv = Point2D(alpha, beta);
                            hit->normal = (alpha * m_na + beta * m_nb + gamma * m_nc).normalized();

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
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray&) const override
        {
            LOG(ERROR) << "Not yet implemented";
            abort();
        }

        math::Box bounding_box() const override
        {
            auto x_interval = interval(minimum(m_a.x(), m_b.x(), m_c.x()), maximum(m_a.x(), m_b.x(), m_c.x()));
            auto y_interval = interval(minimum(m_a.y(), m_b.y(), m_c.y()), maximum(m_a.y(), m_b.y(), m_c.y()));
            auto z_interval = interval(minimum(m_a.z(), m_b.z(), m_c.z()), maximum(m_a.z(), m_b.z(), m_c.z()));

            return Box(x_interval, y_interval, z_interval);
        }

    private:
        math::Point3D m_a, m_b, m_c;
        math::Vector3D m_na, m_nb, m_nc;
        math::Vector3D m_normal;
    };
}

Primitive raytracer::primitives::smooth_triangle(const math::Point3D& a, const math::Point3D& b, const math::Point3D& c, const math::Vector3D& na, const math::Vector3D& nb, const math::Vector3D& nc)
{
    return Primitive(std::make_shared<SmoothTriangleImplementation>(a, b, c, na, nb, nc));
}
