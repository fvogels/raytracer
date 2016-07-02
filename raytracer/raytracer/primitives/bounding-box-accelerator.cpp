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

        return bounding_box_accelerator(group(std::vector<Primitive> { accelerated_union(left_primitives), accelerated_union(right_primitives) }));
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

        return bounding_box_accelerator(group(std::vector<Primitive> { accelerated_union(left_primitives), accelerated_union(right_primitives) }));
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

        return bounding_box_accelerator(group(std::vector<Primitive> { accelerated_union(left_primitives), accelerated_union(right_primitives) }));
    }
}


raytracer::primitives::_private_::BoundingBoxAccelerator::BoundingBoxAccelerator(Primitive child)
    : m_child(child), m_bounding_box(child->bounding_box())
{
    // NOP
}

bool raytracer::primitives::_private_::BoundingBoxAccelerator::find_hit(const math::Ray& ray, Hit* hit) const
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

std::vector<std::shared_ptr<Hit>> raytracer::primitives::_private_::BoundingBoxAccelerator::hits(const math::Ray& ray) const
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

math::Box raytracer::primitives::_private_::BoundingBoxAccelerator::bounding_box() const
{
    return m_bounding_box;
}

Primitive raytracer::primitives::bounding_box_accelerator(Primitive primitive)
{
    return Primitive(std::make_shared<_private_::BoundingBoxAccelerator>(primitive));
}

Primitive raytracer::primitives::accelerated_union(std::vector<Primitive>& primitives)
{
    if (primitives.size() <= 3)
    {
        return bounding_box_accelerator(group(primitives));
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