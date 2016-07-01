#include "primitives/triangle.h"
#include "math/misc.h"
#include <assert.h>
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


raytracer::primitives::_private_::Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c)
    : m_a(a), m_b(b), m_c(c)
{
    m_normal = (b - a).cross(c - a).normalized();
}

bool raytracer::primitives::_private_::Triangle::find_hit(const math::Ray& ray, Hit* hit) const
{
    double denom = m_normal.dot(ray.direction);

    if (denom == approx<double>(0.0))
    {
        return false;
    }
    else
    {
        double numer = -(ray.origin - m_a).dot(m_normal);
        double t = numer / denom;

        if (t > 0)
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

            bool p_is_left_of_ab = ABxAP.dot(m_normal) > 0;
            bool p_is_left_of_bc = BCxBP.dot(m_normal) > 0;
            bool p_is_left_of_ca = CAxCP.dot(m_normal) > 0;

            double gamma = area_ABP / area_ABC;
            double beta = area_BCP / area_ABC;
            double alpha = 1 - beta - gamma;

            if (p_is_left_of_ab && p_is_left_of_bc && p_is_left_of_ca)
            {
                assert(alpha + beta + gamma == approx<double>(1.0));
                //assert(0 <= alpha);
                //assert(0 <= beta);
                //assert(0 <= gamma);

                hit->t = t;
                hit->position = P;
                hit->local_position.xyz = P;
                hit->local_position.uv = Point2D(alpha, beta);
                hit->normal = m_normal;

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

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::Triangle::hits(const math::Ray&) const
{
    // TODO
    abort();
}

Primitive raytracer::primitives::triangle(const math::Point3D& a, const math::Point3D& b, const math::Point3D& c)
{
    return Primitive(std::make_shared<raytracer::primitives::_private_::Triangle>(a, b, c));
}