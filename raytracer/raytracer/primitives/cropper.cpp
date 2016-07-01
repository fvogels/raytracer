#include "primitives/cropper.h"
#include <assert.h>
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


raytracer::primitives::_private_::Cropper::Cropper(Primitive cropped, const math::Function<bool, const math::Point3D&> predicate)
    : m_cropped(cropped), m_predicate(predicate)
{
    assert(cropped);
    assert(predicate);
}

bool raytracer::primitives::_private_::Cropper::find_hit(const math::Ray& ray, Hit* hit) const
{
    auto hs = hits(ray);

    for (auto h : hs)
    {
        assert(h);

        if (h->t > 0)
        {
            *hit = *h;

            return true;
        }
    }

    return false;
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::Cropper::hits(const math::Ray& ray) const
{
    auto hits = m_cropped->hits(ray);

    auto new_end = std::remove_if(hits.begin(), hits.end(), [this](std::shared_ptr<Hit> hit)
    {
        return !this->m_predicate(hit->position);
    });

    hits.erase(new_end, hits.end());

    return hits;
}

Primitive raytracer::primitives::crop(Primitive cropped, math::Function<bool, const Point3D&> predicate)
{
    return Primitive(std::make_shared<_private_::Cropper>(cropped, predicate));
}

Primitive raytracer::primitives::crop_along_x(Primitive cropped, const Interval<double>& x_interval)
{
    std::function<bool(const Point3D&)> predicate = [x_interval](const Point3D& p)
    {
        return x_interval.contains(p.x);
    };

    return crop(cropped, from_lambda<bool, const Point3D&>(predicate));
}

Primitive raytracer::primitives::crop_along_y(Primitive cropped, const Interval<double>& y_interval)
{
    std::function<bool(const Point3D&)> predicate = [y_interval](const Point3D& p)
    {
        return y_interval.contains(p.y);
    };

    return crop(cropped, from_lambda<bool, const Point3D&>(predicate));
}

Primitive raytracer::primitives::crop_along_z(Primitive cropped, const Interval<double>& z_interval)
{
    std::function<bool(const Point3D&)> predicate = [z_interval](const Point3D& p)
    {
        return z_interval.contains(p.z);
    };

    return crop(cropped, from_lambda<bool, const Point3D&>(predicate));
}

Primitive raytracer::primitives::crop_spherical(Primitive cropped, double radius)
{
    std::function<bool(const Point3D&)> predicate = [radius](const Point3D& p)
    {
        return distance(Point3D(0, 0, 0), p) < radius;
    };

    return crop(cropped, from_lambda<bool, const Point3D&>(predicate));
}