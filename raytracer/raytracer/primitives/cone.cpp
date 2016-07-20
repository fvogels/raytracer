#include "primitives/cone.h"
#include "math/misc.h"
#include "math/quadratic_equation.h"
#include "util/misc.h"
#include <assert.h>
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


bool raytracer::primitives::_private_::ConeZ::find_hit(const math::Ray& ray, Hit* hit) const
{
    assert(hit);

    Point2D O2D = point(ray.origin.x(), ray.origin.y());
    Vector2D D2D = vector(ray.direction.x(), ray.direction.y());
    Vector2D OP = O2D - point(0, 0);

    double a = D2D.dot(D2D) - pow(ray.direction.z(), 2);
    double b = 2 * (D2D.dot(OP) - ray.direction.z() * ray.origin.z());
    double c = OP.dot(OP) - pow(ray.origin.z(), 2);

    QuadraticEquation eq(a, b, c);

    if (eq.has_solutions())
    {
        double t1 = eq.x1();
        double t2 = eq.x2();

        sort(t1, t2);

        double t;
        if (0 < t1)
        {
            t = t1;
        }
        else if (0 < t2)
        {
            t = t2;
        }
        else
        {
            return false;
        }

        if (t < hit->t)
        {
            Point3D position = ray.at(t);

            if (position == point(0, 0, 0))
            {
                return false;
            }
            else
            {
                Point2D position_on_circle = point(position.x(), position.y());
                double height = position.z();
                double theta = atan2(position.y(), position.x());

                hit->t = t;
                hit->position = position;
                hit->local_position.xyz = position;
                hit->local_position.uv = point(theta, height);
                hit->normal = vector(position.x(), position.y(), -position.z()).normalized();

                return true;
            }
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

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::ConeZ::hits(const math::Ray& ray) const
{
    // TODO
    abort();
}

math::Box raytracer::primitives::_private_::ConeZ::bounding_box() const
{
    return Box::infinite();
}

Primitive raytracer::primitives::cone_along_z()
{
    return Primitive(std::make_shared<_private_::ConeZ>());
}