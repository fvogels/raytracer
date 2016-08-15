#include "primitives/decorator.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class Decorator : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        Decorator(Material material, Primitive child)
            : m_material(material), m_child(child)
        {
            assert(material);
            assert(child);
        }

        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            Material old_material = hit->material;
            hit->material = Material();

            bool result = m_child->find_first_positive_hit(ray, hit);

            if (result)
            {
                if (!hit->material)
                {
                    hit->material = this->m_material;
                }
            }
            else
            {
                hit->material = old_material;
            }

            assert(!result || hit->material);

            return result;
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            auto hits = this->m_child->find_all_hits(ray);

            for (auto hit : hits)
            {
                if (!hit->material)
                {
                    hit->material = this->m_material;
                }
            }

            return hits;
        }

        math::Box bounding_box() const override
        {
            return m_child->bounding_box();
        }

    private:
        Material m_material;
        Primitive m_child;
    };
}

Primitive raytracer::primitives::decorate(Material material, Primitive child)
{
    return Primitive(std::make_shared<Decorator>(material, child));
}
