#include "primitives/material-scaler.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class MaterialScaler2D : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        MaterialScaler2D(double sx, double sy, Primitive child)
            : m_sx(sx), m_sy(sy), m_child(child)
        {
            // NOP
        }

        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            if (m_child->find_first_positive_hit(ray, hit))
            {
                scale_hit(hit);

                return true;
            }
            else
            {
                return false;
            }
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            auto hits = this->m_child->find_all_hits(ray);

            for (auto hit : hits)
            {
                scale_hit(hit.get());
            }

            return hits;
        }

        math::Box bounding_box() const override
        {
            return m_child->bounding_box();
        }

    private:
        void scale_hit(Hit* hit) const
        {
            hit->local_position.uv.x() *= m_sx;
            hit->local_position.uv.y() *= m_sy;
        }

        double m_sx;
        double m_sy;
        Primitive m_child;
    };
}

Primitive raytracer::primitives::scale_material2d(double sx, double sy, Primitive child)
{
    return Primitive(std::make_shared<MaterialScaler2D>(sx, sy, child));
}
