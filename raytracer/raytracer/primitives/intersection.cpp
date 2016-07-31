#include "primitives/intersection.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
    class Intersection : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        Intersection(Primitive first, Primitive second)
            : m_first(first), m_second(second)
        {
            assert(first);
            assert(second);
        }

        bool find_hit(const Ray& ray, Hit* hit) const override
        {
            auto first_hits = m_first->hits(ray);
            auto second_hits = m_second->hits(ray);

            auto i1 = first_hits.begin();
            auto i2 = second_hits.begin();

            bool inside_first = false;
            bool inside_second = false;

            while (i1 != first_hits.end() && i2 != second_hits.end())
            {
                double t1 = (*i1)->t;
                double t2 = (*i2)->t;

                if (t1 < t2)
                {
                    inside_first = !inside_first;

                    if (inside_second && t1 > 0)
                    {
                        *hit = **i1;

                        return true;
                    }

                    ++i1;
                }
                else
                {
                    inside_second = !inside_second;

                    if (inside_first && t2 > 0)
                    {
                        *hit = **i2;

                        return true;
                    }

                    ++i2;
                }
            }

            return false;
        }

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> result;

            auto first_hits = m_first->hits(ray);
            auto second_hits = m_second->hits(ray);

            auto i1 = first_hits.begin();
            auto i2 = second_hits.begin();

            bool inside_first = false;
            bool inside_second = false;
            bool inside = false;

            while (i1 != first_hits.end() && i2 != second_hits.end())
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
                else
                {
                    inside_second = !inside_second;
                    current_hit = *i2;

                    ++i2;
                }

                bool new_inside = inside_first && inside_second;

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

Primitive raytracer::primitives::intersection(Primitive first, Primitive second)
{
    return Primitive(std::make_shared<Intersection>(first, second));
}
