#include "primitives/plane.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


bool raytracer::primitives::_private_::PlaneXY::find_hit(const Ray& ray, Hit* hit) const
{
    assert(hit != nullptr);

    const Vector3D normal = vector(0, 0, 1);
    double denom = ray.direction.dot(normal);

    if (denom == approx(0.0))
    {
        return false;
    }
    else
    {
        double numer = -((ray.origin - point(0, 0, 0)).dot(normal));
        double t = numer / denom;

        if (0 < t && t < hit->t)
        {
            hit->t = t;
            hit->position = ray.at(hit->t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = point(hit->position.x(), hit->position.y());
            hit->normal = ray.origin.z() > 0 ? normal : -normal;

            return true;
        }
        else
        {
            return false;
        }
    }
}

bool raytracer::primitives::_private_::PlaneXZ::find_hit(const Ray& ray, Hit* hit) const
{
    assert(hit != nullptr);

    const Vector3D normal = vector(0, 1, 0);
    double denom = ray.direction.dot(normal);

    if (denom == approx(0.0))
    {
        return false;
    }
    else
    {
        double numer = -((ray.origin - point(0, 0, 0)).dot(normal));
        double t = numer / denom;

        if (0 < t && t < hit->t)
        {
            hit->t = t;
            hit->position = ray.at(hit->t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = point(hit->position.x(), hit->position.z());
            hit->normal = ray.origin.y() > 0 ? normal : -normal;

            return true;
        }
        else
        {
            return false;
        }
    }
}

bool raytracer::primitives::_private_::PlaneYZ::find_hit(const Ray& ray, Hit* hit) const
{
    assert(hit != nullptr);

    const Vector3D normal = vector(1, 0, 0);
    double denom = ray.direction.dot(normal);

    if (denom == approx(0.0))
    {
        return false;
    }
    else
    {
        double numer = -((ray.origin - point(0, 0, 0)).dot(normal));
        double t = numer / denom;

        if (0 < t && t < hit->t)
        {
            hit->t = t;
            hit->position = ray.at(hit->t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = point(hit->position.y(), hit->position.z());
            hit->normal = ray.origin.x() > 0 ? normal : -normal;

            return true;
        }
        else
        {
            return false;
        }
    }
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::CoordinatePlane::hits(const math::Ray& ray) const
{
    auto hit = std::make_shared<Hit>();

    if (find_hit(ray, hit.get()))
    {
        return std::vector<std::shared_ptr<Hit>> { hit };
    }
    else
    {
        return std::vector<std::shared_ptr<Hit>>();
    }
}

math::Box raytracer::primitives::_private_::PlaneXY::bounding_box() const
{
    return Box(Interval<double>::infinite(), Interval<double>::infinite(), Interval<double>(-0.01, 0.01));
}

math::Box raytracer::primitives::_private_::PlaneXZ::bounding_box() const
{
    return Box(Interval<double>::infinite(), Interval<double>(-0.01, 0.01), Interval<double>::infinite());
}

math::Box raytracer::primitives::_private_::PlaneYZ::bounding_box() const
{
    return Box(Interval<double>(-0.01, 0.01), Interval<double>::infinite(), Interval<double>::infinite());
}

Primitive raytracer::primitives::xy_plane()
{
    return Primitive(std::make_shared<raytracer::primitives::_private_::PlaneXY>());
}

Primitive raytracer::primitives::xz_plane()
{
    return Primitive(std::make_shared<raytracer::primitives::_private_::PlaneXZ>());
}

Primitive raytracer::primitives::yz_plane()
{
    return Primitive(std::make_shared<raytracer::primitives::_private_::PlaneYZ>());
}
