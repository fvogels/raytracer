#include "primitives/difference-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
    class DifferenceImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        DifferenceImplementation(Primitive first, Primitive second)
            : m_first(first), m_second(second)
        {
            assert(first);
            assert(second);
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> result;

            auto first_hits = m_first->find_all_hits(ray);
            auto second_hits = m_second->find_all_hits(ray);

            first_hits.push_back(std::make_shared<Hit>());
            second_hits.push_back(std::make_shared<Hit>());

            auto i1 = first_hits.begin();
            auto i2 = second_hits.begin();

            bool inside_first = false;
            bool inside_second = false;
            bool inside = false;

            while (i1 + 1 != first_hits.end() || i2 + 1 != second_hits.end())
            {
                std::shared_ptr<Hit> current_hit;

                double t1 = (*i1)->t;
                double t2 = (*i2)->t;

                if (t1 < t2)
                {
                    inside_first = !inside_first;
                    current_hit = *i1;

                    ++i1;
                }
                else if ( t1 > t2 )
                {
                    inside_second = !inside_second;
                    current_hit = *i2;

                    ++i2;
                }
                else // t1 == t2
                {
                    inside_first = !inside_first;
                    inside_second = !inside_second;

                    current_hit = *i1;

                    ++i1;
                    ++i2;
                }

                bool new_inside = inside_first && !inside_second;

                if (inside != new_inside)
                {
                    result.push_back(current_hit);
                    inside = new_inside;
                }
            }

            return result;
        }

        math::Box bounding_box() const override
        {
            return m_first->bounding_box().intersect(m_second->bounding_box());
        }

    private:
        Primitive m_first;
        Primitive m_second;
    };
}

Primitive raytracer::primitives::difference(Primitive first, Primitive second)
{
    return Primitive(std::make_shared<DifferenceImplementation>(first, second));
}
