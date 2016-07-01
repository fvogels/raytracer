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
        double u = 0.5 + atan2(p.y, p.x) / (2 * M_PI);
        double v = height;

        assert(0 <= u);
        assert(u <= 1);

        return Point2D(u, v);
    }

    void initialize_hit(Hit* hit, const Ray& ray, double t)
    {
        assert(hit);

        Point3D position = ray.at(t);
        Point2D position_on_circle(position.x, position.y);
        double height = position.x;

        hit->t = t;
        hit->position = position;
        hit->local_position.xyz = position;
        hit->local_position.uv = compute_uv_from_xyz(position_on_circle, height);
        hit->normal = Vector3D(position_on_circle.x, position_on_circle.y, 0);

        assert(hit->normal.is_unit());
    }

    bool find_intersections(const Point2D& O, const Vector2D& D, double* t1, double* t2)
    {
        if ((O - Point2D()).norm_sqr() > 1)
        {
            double a = D.dot(D);
            double b = 2 * D.dot(O - Point2D());
            double c = (O - Point2D()).norm_sqr() - 1;

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
}

bool raytracer::primitives::_private_::Cylinder::find_hit(const Ray& ray, Hit* hit) const
{
    assert(hit != nullptr);

    Point2D O(ray.origin.x, ray.origin.y);
    Vector2D D(ray.direction.x, ray.direction.y);

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

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::Cylinder::hits(const math::Ray& ray) const
{
    Point2D O(ray.origin.x, ray.origin.y);
    Vector2D D(ray.direction.x, ray.direction.y);

    double t1, t2;
    if (find_intersections(O, D, &t1, &t2))
    {
        sort(t1, t2);

        auto hits = std::vector<std::shared_ptr<Hit>>();

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

Primitive raytracer::primitives::cylinder()
{
    return Primitive(std::make_shared<raytracer::primitives::_private_::Cylinder>());
}