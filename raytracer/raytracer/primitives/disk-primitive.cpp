#include "primitives/disk-primitive.h"
#include "primitives/transformer-primitive.h"
#include "math/misc.h"
#include "math/interval.h"
#include <assert.h>
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


namespace
{
    class DiskImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    private:
        double m_radius;

    public:
        DiskImplementation(double radius)
            : m_radius(radius)
        {
            assert(radius >= 0);
        }

        bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
        {
            assert(hit);

            if (ray.direction.y() == 0)
            {
                return false;
            }
            else
            {
                double t = -ray.origin.y() / ray.direction.y();
                Point3D p = ray.at(t);
                double r = distance(Point3D(0, 0, 0), p);

                if (r < 1 && interval(0.0, hit->t).contains(t))
                {
                    hit->t = t;
                    hit->normal = Vector3D(0, sign(ray.origin.y()), 0);
                    hit->position = p;
                    hit->local_position.xyz = p;

                    Cartesian2D cartesian_coordinates{ p.x(), p.z() };
                    Polar polar_coordinates = convert_coordinates<Polar>(cartesian_coordinates);
                    hit->local_position.uv = Point2D(polar_coordinates.radius, polar_coordinates.theta.degrees() / 360.0);

                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

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

        math::Box bounding_box() const override
        {
            return Box(interval(-1.0, 1.0), interval(-0.01, 0.01), interval(-1.0, 1.0));
        }
    };
}

Primitive raytracer::primitives::xy_disk(double radius)
{
    return rotate_around_x(90_degrees, xz_disk(radius));
}

Primitive raytracer::primitives::xz_disk(double radius)
{
    return Primitive(std::make_shared<DiskImplementation>(radius));
}

Primitive raytracer::primitives::yz_disk(double radius)
{
    return rotate_around_z(90_degrees, xz_disk(radius));
}
