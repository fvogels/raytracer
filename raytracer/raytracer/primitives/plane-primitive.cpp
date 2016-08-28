#include "primitives/plane-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class CoordinatePlane : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            auto hit = std::make_shared<Hit>();

            if (find_first_positive_hit(ray, hit.get()))
            {
                return std::vector<std::shared_ptr<Hit>> { hit };
            }
            else
            {
                return std::vector<std::shared_ptr<Hit>>();
            }
        }
    };

    class PlaneXY : public CoordinatePlane
    {
    public:
        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            assert(hit != nullptr);

            const Vector3D normal = Vector3D(0, 0, 1);
            double denom = ray.direction.dot(normal);

            if (denom == approx(0.0))
            {
                return false;
            }
            else
            {
                double numer = -((ray.origin - Point3D(0, 0, 0)).dot(normal));
                double t = numer / denom;

                if (0 < t && t < hit->t)
                {
                    hit->t = t;
                    hit->position = ray.at(hit->t);
                    hit->local_position.xyz = hit->position;
                    hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
                    hit->normal = ray.origin.z() > 0 ? normal : -normal;

                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        math::Box bounding_box() const override
        {
            return Box(Interval<double>::infinite(), Interval<double>::infinite(), interval(-0.01, 0.01));
        }
    };

    class PlaneXZ : public CoordinatePlane
    {
    public:
        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            assert(hit != nullptr);

            const Vector3D normal = Vector3D(0, 1, 0);
            double denom = ray.direction.dot(normal);

            if (denom == approx(0.0))
            {
                return false;
            }
            else
            {
                double numer = -((ray.origin - Point3D(0, 0, 0)).dot(normal));
                double t = numer / denom;

                if (0 < t && t < hit->t)
                {
                    hit->t = t;
                    hit->position = ray.at(hit->t);
                    hit->local_position.xyz = hit->position;
                    hit->local_position.uv = Point2D(hit->position.x(), hit->position.z());
                    hit->normal = ray.origin.y() > 0 ? normal : -normal;

                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        math::Box bounding_box() const override
        {
            return Box(Interval<double>::infinite(), interval(-0.01, 0.01), Interval<double>::infinite());
        }
    };

    class PlaneYZ : public CoordinatePlane
    {
    public:
        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            assert(hit != nullptr);

            const Vector3D normal = Vector3D(1, 0, 0);
            double denom = ray.direction.dot(normal);

            if (denom == approx(0.0))
            {
                return false;
            }
            else
            {
                double numer = -((ray.origin - Point3D(0, 0, 0)).dot(normal));
                double t = numer / denom;

                if (0 < t && t < hit->t)
                {
                    hit->t = t;
                    hit->position = ray.at(hit->t);
                    hit->local_position.xyz = hit->position;
                    hit->local_position.uv = Point2D(hit->position.y(), hit->position.z());
                    hit->normal = ray.origin.x() > 0 ? normal : -normal;

                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        math::Box bounding_box() const override
        {
            return Box(interval(-0.01, 0.01), Interval<double>::infinite(), Interval<double>::infinite());
        }
    };
}

Primitive raytracer::primitives::xy_plane()
{
    return Primitive(std::make_shared<PlaneXY>());
}

Primitive raytracer::primitives::xz_plane()
{
    return Primitive(std::make_shared<PlaneXZ>());
}

Primitive raytracer::primitives::yz_plane()
{
    return Primitive(std::make_shared<PlaneYZ>());
}
