#include "primitives/unify.h"


using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class Unificator : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        Unificator(Primitive child)
            : m_child(child)
        {
            // NOP
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            auto hits = m_child->find_all_hits(ray);

            for (auto& hit : hits)
            {
                hit->local_position.xyz = hit->position;
            }

            return hits;
        }

        bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const
        {
            if (m_child->find_first_positive_hit(ray, hit))
            {
                hit->local_position.xyz = hit->position;

                return true;
            }
            else
            {
                return false;
            }
        }

        math::Box bounding_box() const
        {
            return m_child->bounding_box();
        }

    private:
        Primitive m_child;
    };
}


Primitive raytracer::primitives::unify(Primitive child)
{
    return Primitive(std::make_shared<Unificator>(child));
}
