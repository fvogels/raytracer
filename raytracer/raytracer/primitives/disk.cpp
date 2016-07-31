#include "primitives/disk.h"
#include "math/misc.h"
#include <assert.h>
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;

namespace
{
    class Disk : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        bool find_hit(const math::Ray& ray, Hit* hit) const override
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
                double r = distance(point(0, 0, 0), p);

                if (t < hit->t && t < 1)
                {
                    hit->t = t;
                    hit->normal = vector(0, sign(ray.origin.y()), 0);
                    hit->position = p;
                    hit->local_position.xyz = p;
                    hit->local_position.uv = point(r, atan2(p.z(), p.x()));

                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray& ray) const override
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

        math::Box bounding_box() const override
        {
            return Box(Interval<double>(-1, 1), Interval<double>(-0.01, 0.01), Interval<double>(-1, 1));
        }
    };
}

Primitive raytracer::primitives::disk()
{
    return Primitive(std::make_shared<Disk>());
}