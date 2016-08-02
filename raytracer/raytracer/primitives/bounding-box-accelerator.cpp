#include "primitives/bounding-box-accelerator.h"
#include "primitives/union.h"
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


namespace
{
    Box box_around_all(const std::vector<Primitive>& primitives)
    {
        Box result = Box::empty();

        for (auto primitive : primitives)
        {
            result = result.merge(primitive->bounding_box());
        }

        return result;
    }

    Primitive accelerated_union_along_x(std::vector<Primitive>& primitives)
    {
        std::sort(primitives.begin(), primitives.end(), [](Primitive p, Primitive q)
        {
            return p->bounding_box().x().upper < q->bounding_box().x().upper;
        });

        auto middle = primitives.begin() + primitives.size() / 2;

        std::vector<Primitive> left_primitives(primitives.begin(), middle);
        std::vector<Primitive> right_primitives(middle, primitives.end());
        std::vector<Primitive> all_primitives = { accelerated_union(left_primitives), accelerated_union(right_primitives) };
        return bounding_box_accelerator(make_union(all_primitives));
    }

    Primitive accelerated_union_along_y(std::vector<Primitive>& primitives)
    {
        std::sort(primitives.begin(), primitives.end(), [](Primitive p, Primitive q)
        {
            return p->bounding_box().y().upper < q->bounding_box().y().upper;
        });

        auto middle = primitives.begin() + primitives.size() / 2;

        std::vector<Primitive> left_primitives(primitives.begin(), middle);
        std::vector<Primitive> right_primitives(middle, primitives.end());
        std::vector<Primitive> all_primitives = { accelerated_union(left_primitives), accelerated_union(right_primitives) };

        return bounding_box_accelerator(make_union(all_primitives));
    }

    Primitive accelerated_union_along_z(std::vector<Primitive>& primitives)
    {
        std::sort(primitives.begin(), primitives.end(), [](Primitive p, Primitive q)
        {
            return p->bounding_box().z().upper < q->bounding_box().z().upper;
        });

        auto middle = primitives.begin() + primitives.size() / 2;

        std::vector<Primitive> left_primitives(primitives.begin(), middle);
        std::vector<Primitive> right_primitives(middle, primitives.end());
        std::vector<Primitive> all_primitives = { accelerated_union(left_primitives), accelerated_union(right_primitives) };

        return bounding_box_accelerator(make_union(all_primitives));
    }

    class BoundingBoxAccelerator : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        BoundingBoxAccelerator(Primitive child)
            : m_child(child), m_bounding_box(child->bounding_box())
        {
            // NOP
        }

        bool find_hit(const math::Ray& ray, Hit* hit) const override
        {
            if (m_bounding_box.is_hit_positively_by(ray))
            {
                return m_child->find_hit(ray, hit);
            }
            else
            {
                assert(!m_child->find_hit(ray, hit));

                return false;
            }
        }

        std::vector<std::shared_ptr<Hit>> hits(const math::Ray& ray) const override
        {
            if (m_bounding_box.is_hit_by(ray))
            {
                return m_child->hits(ray);
            }
            else
            {
                return std::vector<std::shared_ptr<Hit>>();
            }
        }

        math::Box bounding_box() const override
        {
            return m_bounding_box;
        }

    private:
        Primitive m_child;
        math::Box m_bounding_box;
    };
}

Primitive raytracer::primitives::bounding_box_accelerator(Primitive primitive)
{
    return Primitive(std::make_shared<BoundingBoxAccelerator>(primitive));
}

Primitive raytracer::primitives::accelerated_union(std::vector<Primitive>& primitives)
{
    if (primitives.size() <= 3)
    {
        return bounding_box_accelerator(make_union(primitives));
    }
    else
    {
        Box box = box_around_all(primitives);

        if (box.x().size() >= box.y().size())
        {
            if (box.x().size() >= box.z().size())
            {
                return accelerated_union_along_x(primitives);
            }
            else
            {
                return accelerated_union_along_z(primitives);
            }
        }
        else if (box.y().size() > box.z().size())
        {
            return accelerated_union_along_y(primitives);
        }
        else
        {
            return accelerated_union_along_z(primitives);
        }
    }
}
