#define _USE_MATH_DEFINES
#include "primitives/cylinder.h"
#include "materials/material.h"
#include "util/misc.h"
#include "math/quadratic_equation.h"
#include <assert.h>
#include <math.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    Point2D compute_uv_from_xyz(const Point2D& p, double height)
    {
        double u = 0.5 + atan2(p.y(), p.x()) / (2 * M_PI);
        double v = height;

        assert(0 <= u);
        assert(u <= 1);

        return point(u, v);
    }

    void initialize_hit_x_cylinder(Hit* hit, const Ray& ray, double t)
    {
        assert(hit);

        Point3D position = ray.at(t);
        Point2D position_on_circle = point(position.y(), position.z());
        double height = position.x();

        hit->t = t;
        hit->position = position;
        hit->local_position.xyz = position;
        hit->local_position.uv = compute_uv_from_xyz(position_on_circle, height);
        hit->normal = vector(0.0, position.y(), position.z());

        assert(hit->normal.is_unit());
    }

    void initialize_hit_y_cylinder(Hit* hit, const Ray& ray, double t)
    {
        assert(hit);

        Point3D position = ray.at(t);
        Point2D position_on_circle = point(position.x(), position.z());
        double height = position.y();

        hit->t = t;
        hit->position = position;
        hit->local_position.xyz = position;
        hit->local_position.uv = compute_uv_from_xyz(position_on_circle, height);
        hit->normal = vector(position.x(), 0.0, position.z());

        assert(hit->normal.is_unit());
    }

    void initialize_hit_z_cylinder(Hit* hit, const Ray& ray, double t)
    {
        assert(hit);

        Point3D position = ray.at(t);
        Point2D position_on_circle = point(position.x(), position.y());
        double height = position.z();

        hit->t = t;
        hit->position = position;
        hit->local_position.xyz = position;
        hit->local_position.uv = compute_uv_from_xyz(position_on_circle, height);
        hit->normal = vector(position.x(), position.y(), 0);

        assert(hit->normal.is_unit());
    }

    bool find_intersections(const Point2D& O, const Vector2D& D, double* t1, double* t2)
    {
        if ((O - point(0, 0)).norm_sqr() > 1)
        {
            double a = D.dot(D);
            double b = 2 * D.dot(O - point(0, 0));
            double c = (O - point(0, 0)).norm_sqr() - 1;

            QuadraticEquation eq(a, b, c);

            if (eq.has_solutions())
            {
                *t1 = eq.x1();
                *t2 = eq.x2();

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

    class CylinderX : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        bool find_hit(const Ray& ray, Hit* hit) const override
        {
            assert(hit != nullptr);

            auto O = point(ray.origin.y(), ray.origin.z());
            auto D = vector(ray.direction.y(), ray.direction.z());

            double t1, t2;
            if (find_intersections(O, D, &t1, &t2))
            {
                double t;
                if (!smallest_greater_than_zero(t1, t2, &t))
                {
                    // Both hits are behind the eye
                    return false;
                }

                if (t < hit->t)
                {
                    initialize_hit_x_cylinder(hit, ray, t);

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

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray& ray) const override
        {
            Point2D O = point(ray.origin.y(), ray.origin.z());
            Vector2D D = vector(ray.direction.y(), ray.direction.z());

            double t1, t2;
            if (find_intersections(O, D, &t1, &t2))
            {
                sort(t1, t2);

                auto hits = std::vector<std::shared_ptr<Hit>>();

                auto hit1 = std::make_shared<Hit>();
                auto hit2 = std::make_shared<Hit>();

                initialize_hit_x_cylinder(hit1.get(), ray, t1);
                initialize_hit_x_cylinder(hit2.get(), ray, t2);

                hits.push_back(hit1);
                hits.push_back(hit2);

                return hits;
            }
            else
            {
                return std::vector<std::shared_ptr<Hit>>();
            }
        }

        Box bounding_box() const override
        {
            return Box(Interval<double>::infinite(), Interval<double>(-1, 1), Interval<double>(-1, 1));
        }
    };

    class CylinderY : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        bool find_hit(const Ray& ray, Hit* hit) const override
        {
            assert(hit != nullptr);

            Point2D O = point(ray.origin.x(), ray.origin.z());
            Vector2D D = vector(ray.direction.x(), ray.direction.z());

            double t1, t2;
            if (find_intersections(O, D, &t1, &t2))
            {
                double t;
                if (!smallest_greater_than_zero(t1, t2, &t))
                {
                    // Both hits are behind the eye
                    return false;
                }

                if (t < hit->t)
                {
                    initialize_hit_y_cylinder(hit, ray, t);

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

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray& ray) const override
        {
            Point2D O = point(ray.origin.x(), ray.origin.z());
            Vector2D D = vector(ray.direction.x(), ray.direction.z());

            double t1, t2;
            if (find_intersections(O, D, &t1, &t2))
            {
                sort(t1, t2);

                auto hits = std::vector<std::shared_ptr<Hit>>();

                auto hit1 = std::make_shared<Hit>();
                auto hit2 = std::make_shared<Hit>();

                initialize_hit_y_cylinder(hit1.get(), ray, t1);
                initialize_hit_y_cylinder(hit2.get(), ray, t2);

                hits.push_back(hit1);
                hits.push_back(hit2);

                return hits;
            }
            else
            {
                return std::vector<std::shared_ptr<Hit>>();
            }
        }

        Box bounding_box() const override
        {
            return Box(Interval<double>(-1, 1), Interval<double>::infinite(), Interval<double>(-1, 1));
        }
    };

    class CylinderZ : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        bool find_hit(const Ray& ray, Hit* hit) const override
        {
            assert(hit != nullptr);

            Point2D O = point(ray.origin.x(), ray.origin.y());
            Vector2D D = vector(ray.direction.x(), ray.direction.y());

            double t1, t2;
            if (find_intersections(O, D, &t1, &t2))
            {
                double t;
                if (!smallest_greater_than_zero(t1, t2, &t))
                {
                    // Both hits are behind the eye
                    return false;
                }

                if (t < hit->t)
                {
                    initialize_hit_z_cylinder(hit, ray, t);

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

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray& ray) const override
        {
            Point2D O = point(ray.origin.x(), ray.origin.y());
            Vector2D D = vector(ray.direction.x(), ray.direction.y());

            double t1, t2;
            if (find_intersections(O, D, &t1, &t2))
            {
                sort(t1, t2);

                auto hits = std::vector<std::shared_ptr<Hit>>();

                auto hit1 = std::make_shared<Hit>();
                auto hit2 = std::make_shared<Hit>();

                initialize_hit_z_cylinder(hit1.get(), ray, t1);
                initialize_hit_z_cylinder(hit2.get(), ray, t2);

                hits.push_back(hit1);
                hits.push_back(hit2);

                return hits;
            }
            else
            {
                return std::vector<std::shared_ptr<Hit>>();
            }
        }

        Box bounding_box() const override
        {
            return Box(Interval<double>(-1, 1), Interval<double>(-1, 1), Interval<double>::infinite());
        }
    };
}

Primitive raytracer::primitives::cylinder_along_x()
{
    return Primitive(std::make_shared<CylinderX>());
}

Primitive raytracer::primitives::cylinder_along_y()
{
    return Primitive(std::make_shared<CylinderY>());
}

Primitive raytracer::primitives::cylinder_along_z()
{
    return Primitive(std::make_shared<CylinderZ>());
}