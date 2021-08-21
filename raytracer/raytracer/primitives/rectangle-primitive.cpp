#include "primitives/rectangle-primitive.h"
#include "primitives/transformer-primitive.h"
#include "math/interval.h"
#include "math/misc.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class RectangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    private:
        double m_x_size;
        double m_y_size;

    public:
        RectangleImplementation(double x_size, double y_size)
            : m_x_size(x_size), m_y_size(y_size)
        {
            // NOP
        }

        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            if (ray.direction.z() == 0)
            {
                return false;
            }
            else
            {
                double t = -ray.origin.z() / ray.direction.z();

                if (interval(0.0, hit->t).contains(t))
                {
                    Point3D p = ray.at(t);

                    if (interval(-m_x_size / 2, m_x_size / 2).contains(p.x()) && interval(-m_y_size / 2, m_y_size / 2).contains(p.y()))
                    {
                        hit->t = t;
                        hit->normal = Vector3D(0, 0, sign(ray.origin.z()));
                        hit->position = p;
                        hit->local_position.xyz = p;
                        hit->local_position.uv = Point2D(p.x(), p.y());

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
            if (ray.direction.z() == 0)
            {
                return std::vector<std::shared_ptr<Hit>>();
            }
            else
            {
                double t = -ray.origin.z() / ray.direction.z();
                Point3D p = ray.at(t);

                if (interval(-m_x_size / 2, m_x_size / 2).contains(p.x()) && interval(-m_y_size, m_y_size).contains(p.y()))
                {
                    auto hit = std::make_shared<Hit>();

                    hit->t = t;
                    hit->normal = Vector3D(0, 0, sign(ray.origin.y()));
                    hit->position = p;
                    hit->local_position.xyz = p;
                    hit->local_position.uv = Point2D(p.x(), p.y());

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
            return Box(interval(-1.0, 1.0), interval(-1.0, 1.0), interval(-0.001, 0.001));
        }
    };
}

Primitive raytracer::primitives::xy_rectangle(double x_size, double y_size)
{
    return Primitive(std::make_shared<RectangleImplementation>(x_size, y_size));
}

Primitive raytracer::primitives::xz_rectangle(double x_size, double z_size)
{
    return rotate_around_x(90_degrees, xy_rectangle(x_size, z_size));
}

Primitive raytracer::primitives::yz_rectangle(double y_size, double z_size)
{
    return rotate_around_y(90_degrees, xy_rectangle(z_size, y_size));
}
