#include "primitives/union.h"
#include <algorithm>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
    class Union : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        Union(std::vector<Primitive>& children)
            : children(children)
        {
            // NOP
        }

        bool find_hit(const Ray& ray, Hit* hit) const override
        {
            bool found_hit = false;

            for (const auto& child : this->children)
            {
                found_hit = child->find_hit(ray, hit) || found_hit;
            }

            return found_hit;
        }

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> hits;

            for (const auto& child : this->children)
            {
                for (auto hit : child->hits(ray))
                {
                    hits.push_back(hit);
                }
            }

            std::sort(hits.begin(), hits.end(), [](const std::shared_ptr<Hit>& h1, const std::shared_ptr<Hit>& h2)
            {
                return h1->t < h2->t;
            });

            return hits;
        }

        math::Box bounding_box() const override
        {
            Box result = Box::empty();

            for (auto child : this->children)
            {
                Box child_box = child->bounding_box();
                result = result.merge(child_box);
            }

            return result;
        }

    private:
        std::vector<Primitive> children;
    };
}

Primitive raytracer::primitives::make_union(std::vector<Primitive>& children)
{
    return Primitive(std::make_shared<Union>(children));
}