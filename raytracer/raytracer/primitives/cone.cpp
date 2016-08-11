#include "primitives/cone.h"
#include "math/misc.h"
#include "math/quadratic_equation.h"
#include "util/misc.h"
#include "easylogging++.h"
#include <assert.h>
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


namespace
{
    class ConeZ : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        bool find_hit(const math::Ray& ray, Hit* hit) const override
        {
            assert(hit);

            Point2D O2D = Point2D(ray.origin.x(), ray.origin.y());
            Vector2D D2D = Vector2D(ray.direction.x(), ray.direction.y());
            Vector2D OP = O2D - Point2D(0, 0);

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

                    if (position == Point3D(0, 0, 0))
                    {
                        return false;
                    }
                    else
                    {
                        Point2D position_on_circle(position.x(), position.y());
                        double height = position.z();
                        double theta = atan2(position_on_circle.y(), position_on_circle.x());

                        hit->t = t;
                        hit->position = position;
                        hit->local_position.xyz = position;
                        hit->local_position.uv = Point2D(theta, height);
                        hit->normal = Vector3D(position.x(), position.y(), -position.z()).normalized();

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

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override
        {
            LOG(ERROR) << "Not yet implemented: Cone::hits";

            // TODO
            abort();
        }

        math::Box bounding_box() const override
        {
            // TODO
            return Box::infinite();
        }
    };
}

Primitive raytracer::primitives::cone_along_z()
{
    return Primitive(std::make_shared<ConeZ>());
}
