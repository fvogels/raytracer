#include "primitives/group-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;

namespace
{
    class Group : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        Group(unsigned id, Primitive child)
            : m_child(child), m_id(id)
        {
            // NOP
        }

        bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
        {
            if (m_child->find_first_positive_hit(ray, hit))
            {
                hit->group_id = m_id;

                return true;
            }
            else
            {
                return false;
            }
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            auto hit_list = m_child->find_all_hits(ray);

            for (auto& hit : hit_list)
            {
                if (hit->group_id == MISSING_ID)
                {
                    hit->group_id = m_id;
                }
            }

            return hit_list;
        }

        math::Box bounding_box() const override
        {
            return m_child->bounding_box();
        }

    private:
        Primitive m_child;
        unsigned m_id;
    };
}

Primitive raytracer::primitives::group(unsigned id, Primitive child)
{
    return Primitive(std::make_shared<Group>(id, child));
}
