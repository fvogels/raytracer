#define _USE_MATH_DEFINES
#include "primitives/sphere-primitive.h"
#include "materials/material.h"
#include "util/misc.h"
#include "math/coordinate-systems.h"
#include <assert.h>
#include <math.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
    class SphereImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            assert(hit != nullptr);

            double a = ray.direction.dot(ray.direction);
            double b = 2 * ray.direction.dot(ray.origin - Point3D(0, 0, 0));
            double c = (ray.origin - Point3D()).norm_sqr() - 1;
            double d = b * b - 4 * a * c;

            if (d >= 0)
            {
                double sqrt_d = sqrt(d);

                // Compute t's at which ray intersects sphere
                double t1 = (-b - sqrt_d) / (2 * a);
                double t2 = (-b + sqrt_d) / (2 * a);

                // Find closest t > 0
                double t;

                if (t1 > t2)
                {
                    swap(t1, t2);
                }

                if (t1 > 0)
                {
                    t = t1;
                }
                else if (t2 > 0)
                {
                    t = t2;
                }
                else
                {
                    // Both hits occur behind the eye
                    return false;
                }

                if (t < hit->t)
                {
                    initialize_hit(hit, ray, t);

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

        std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
        {
            double a = ray.direction.dot(ray.direction);
            double b = 2 * ray.direction.dot(ray.origin - Point3D());
            double c = (ray.origin - Point3D()).norm_sqr() - 1;
            double d = b * b - 4 * a * c;

            if (d >= 0)
            {
                double sqrt_d = sqrt(d);

                double t1 = (-b - sqrt_d) / (2 * a);
                double t2 = (-b + sqrt_d) / (2 * a);

                if (t1 > t2)
                {
                    swap(t1, t2);
                }

                std::vector<std::shared_ptr<Hit>> hits;

                auto hit1 = std::make_shared<Hit>();
                auto hit2 = std::make_shared<Hit>();

                initialize_hit(hit1.get(), ray, t1);
                initialize_hit(hit2.get(), ray, t2);

                hits.push_back(hit1);
                hits.push_back(hit2);

                return hits;
            }
            else
            {
                return std::vector<std::shared_ptr<Hit>>();
            }
        }

        math::Box bounding_box() const override
        {
            auto range = interval(-1.0, 1.0);

            return Box(range, range, range);
        }

    private:
        Point2D compute_uv_from_xyz(const Point3D& p) const
        {
            Cartesian3D cartesian{ p.x(), p.y(), p.z() };
            Spherical spherical = convert_coordinates<Spherical>(cartesian);

            double u = Interval<Angle>(-180_degrees, 180_degrees).to_relative(spherical.azimuth);
            double v = Interval<Angle>(90_degrees, -90_degrees).to_relative(spherical.elevation);

            assert(0 <= u);
            assert(u <= 1);
            assert(0 <= v);
            assert(v <= 1);

            return Point2D(u, v);
        }

        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            hit->t = t;
            hit->position = ray.at(t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = compute_uv_from_xyz(hit->position);
            hit->normal = compute_normal_at(ray, hit->position);

            assert(is_on_sphere(hit->position));
        }

        Vector3D compute_normal_at(const Ray& ray, const Point3D& position) const
        {
            assert(is_on_sphere(position));

            Vector3D outward_normal = position - Point3D();
            return ray.direction.dot(outward_normal) < 0 ? outward_normal : -outward_normal;
        }

        bool is_on_sphere(const Point3D& p) const
        {
            return distance(Point3D(0, 0, 0), p) == approx(1.0);
        }
    };
}

Primitive raytracer::primitives::sphere()
{
    return Primitive(std::make_shared<SphereImplementation>());
}