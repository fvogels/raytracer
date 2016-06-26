#define _USE_MATH_DEFINES
#include "Sphere.h"
#include "materials/material.h"
#include "util/misc.h"
#include <assert.h>
#include <math.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
    Point2D compute_uv_from_xyz(const Point3D& p)
    {
        double u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
        double v = 0.5 - asin(p.y) / M_PI;

        assert(0 <= u);
        assert(u <= 1);
        assert(0 <= v);
        assert(v <= 1);

        return Point2D(u, v);
    }

    void initialize_hit(Hit* hit, const Ray& ray, double t)
    {
        hit->t = t;
        hit->position = ray.at(t);
        hit->local_position.xyz = hit->position;
        hit->local_position.uv = compute_uv_from_xyz(hit->position);
        hit->normal = hit->position - Point3D();
    }
}

bool raytracer::primitives::Sphere::find_hit(const Ray& ray, Hit* hit) const
{
    assert(hit != nullptr);

    double a = ray.direction.dot(ray.direction);
    double b = 2 * ray.direction.dot(ray.origin - Point3D());
    double c = (ray.origin - Point3D()).norm_sqr() - 1;
    double d = b * b - 4 * a * c;

    if (d >= 0)
    {
        double sqrt_d = std::sqrt(d);

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

std::vector<std::shared_ptr<Hit>> raytracer::primitives::Sphere::hits(const Ray& ray) const
{
    double a = ray.direction.dot(ray.direction);
    double b = 2 * ray.direction.dot(ray.origin - Point3D());
    double c = (ray.origin - Point3D()).norm_sqr() - 1;
    double d = b * b - 4 * a * c;

    if (d >= 0)
    {
        double sqrt_d = std::sqrt(d);

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