#include "primitives/square-primitive.h"
#include "math/interval.h"
#include "math/misc.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class SquareXZImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            if (ray.direction.y() == 0)
            {
                return false;
            }
            else
            {
                double t = -ray.origin.y() / ray.direction.y();

                if (interval(0.0, hit->t).contains(t))
                {
                    Point3D p = ray.at(t);

                    if (interval(0.0, 1.0).contains(p.x()) && interval(0.0, 1.0).contains(p.z()))
                    {
                        hit->t = t;
                        hit->normal = Vector3D(0, sign(ray.origin.y()), 0);
                        hit->position = p;
                        hit->local_position.xyz = p;
                        hit->local_position.uv = Point2D(p.x(), p.z());

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

        std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
        {
            if (ray.direction.y() == 0)
            {
                return std::vector<std::shared_ptr<Hit>>();
            }
            else
            {
                double t = -ray.origin.y() / ray.direction.y();
                Point3D p = ray.at(t);
                
                if (interval(0.0, 1.0).contains(p.x()) && interval(0.0, 1.0).contains(p.z()))
                {
                    auto hit = std::make_shared<Hit>();

                    hit->t = t;
                    hit->normal = Vector3D(0, sign(ray.origin.y()), 0);
                    hit->position = p;
                    hit->local_position.xyz = p;
                    hit->local_position.uv = Point2D(p.x(), p.z());
                    
                    std::vector<std::shared_ptr<Hit>> hits = { hit };
                    return hits;
                }
                else
                {
                    return std::vector<std::shared_ptr<Hit>>();
                }
            }
        }

        math::Box bounding_box() const override
        {
            return Box(interval(0.0, 1.0), interval(-0.001, 0.001), interval(0.0, 1.0));
        }
    };
}

Primitive raytracer::primitives::xz_square()
{
    return Primitive(std::make_shared<SquareXZImplementation>());
}