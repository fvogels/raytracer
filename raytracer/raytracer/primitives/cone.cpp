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
        bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
        {
            assert(hit);

            Point2D Oxy = Point2D(ray.origin.x(), ray.origin.y());
            Vector2D Dxy = Vector2D(ray.direction.x(), ray.direction.y());
            Vector2D Vxy = Oxy - Point2D(0, 0);

            double a = Dxy.dot(Dxy) - pow(ray.direction.z(), 2);
            double b = 2 * (Dxy.dot(Vxy) - ray.direction.z() * ray.origin.z());
            double c = Vxy.dot(Vxy) - pow(ray.origin.z(), 2);

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
                    return compute_hit_at(ray, t, hit);
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

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray& ray) const override
        {
            Point2D Oxy = Point2D(ray.origin.x(), ray.origin.y());
            Vector2D Dxy = Vector2D(ray.direction.x(), ray.direction.y());
            Vector2D Vxy = Oxy - Point2D(0, 0);

            double a = Dxy.dot(Dxy) - pow(ray.direction.z(), 2);
            double b = 2 * (Dxy.dot(Vxy) - ray.direction.z() * ray.origin.z());
            double c = Vxy.dot(Vxy) - pow(ray.origin.z(), 2);

            QuadraticEquation quadratic_equation(a, b, c);

            if (quadratic_equation.has_solutions())
            {
                std::vector<std::shared_ptr<Hit>> hits;

                double t1 = quadratic_equation.x1();
                double t2 = quadratic_equation.x2();

                sort(t1, t2);

                auto hit1 = std::make_shared<Hit>();
                auto hit2 = std::make_shared<Hit>();

                if (compute_hit_at(ray, t1, hit1.get())) { hits.push_back(hit1); }
                if (compute_hit_at(ray, t2, hit2.get())) { hits.push_back(hit2); }

                return hits;
            }
            else
            {
                return std::vector<std::shared_ptr<Hit>>();
            }
        }

        math::Box bounding_box() const override
        {
            return Box::infinite();
        }

    private:
        /// <summary>
        /// Computes the hit data. The (0,0,0) point is problematic, so it is not considered to be part of the cone,
        /// hence the need for a return value.
        /// </summary>
        /// <param name="ray">Ray that intersects the cone.</param>
        /// <param name="t">T-value at which the ray hits the cone.</param>
        /// <param name="hit">Hit object to be filled in.</param>
        /// <returns>True if it's a valid hit, false otherwise.</returns>
        bool compute_hit_at(const Ray& ray, double t, Hit* hit) const
        {
            Point3D position = ray.at(t);

            assert(lies_on_cone(position));

            if (position == Point3D(0, 0, 0))
            {
                return false;
            }
            else
            {
                Point2D position_on_circle(position.x(), position.y());
                double height = position.z();
                double theta = atan2(position_on_circle.y(), position_on_circle.x());
                Vector3D outward_normal = Vector3D(position.x(), position.y(), -position.z()).normalized();

                hit->t = t;
                hit->position = position;
                hit->local_position.xyz = position;
                hit->local_position.uv = Point2D(theta, height);
                hit->normal = outward_normal.dot(ray.direction) < 0 ? outward_normal : -outward_normal;

                return true;
            }
        }

        /// <summary>
        /// Checks whether <paramref name="p" /> lies on the cone. (0,0,0) is considered part of the cone by this method.
        /// </summary>
        bool lies_on_cone(const Point3D& p) const
        {
            double distance_from_z_axis = sqrt(pow(p.x(), 2) + pow(p.y(), 2));

            return distance_from_z_axis == approx(std::abs(p.z()));
        }
    };
}

Primitive raytracer::primitives::cone_along_z()
{
    return Primitive(std::make_shared<ConeZ>());
}
