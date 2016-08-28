#include "primitives/bumpifier-primitive.h"
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


namespace
{
    class Bumpifier2DImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        Bumpifier2DImplementation(math::Function<math::Vector3D(const math::Point2D&)> normal_perturbator, Primitive perturbee)
            : m_normal_perturbator(normal_perturbator), m_perturbee(perturbee) { }

        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            if (m_perturbee->find_first_positive_hit(ray, hit))
            {
                perturb(hit);

                return true;
            }
            else
            {
                return false;
            }
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            auto hits = m_perturbee->find_all_hits(ray);

            for (auto& hit : hits)
            {
                perturb(hit.get());
            }

            return hits;
        }

        math::Box bounding_box() const override
        {
            return m_perturbee->bounding_box();
        }

    private:
        void perturb(Hit* hit) const
        {
            hit->normal = (hit->normal + m_normal_perturbator(hit->local_position.uv)).normalized();
        }

        math::Function<math::Vector3D(const math::Point2D&)> m_normal_perturbator;
        Primitive m_perturbee;
    };

    class Bumpifier3DImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        Bumpifier3DImplementation(math::Function<math::Vector3D(const math::Point3D&)> normal_perturbator, Primitive perturbee)
            : m_normal_perturbator(normal_perturbator), m_perturbee(perturbee) { }

        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            if (m_perturbee->find_first_positive_hit(ray, hit))
            {
                perturb(hit);

                return true;
            }
            else
            {
                return false;
            }
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            auto hits = m_perturbee->find_all_hits(ray);

            for (auto& hit : hits)
            {
                perturb(hit.get());
            }

            return hits;
        }

        math::Box bounding_box() const override
        {
            return m_perturbee->bounding_box();
        }

    private:
        void perturb(Hit* hit) const
        {
            hit->normal = (hit->normal + m_normal_perturbator(hit->local_position.xyz)).normalized();
        }

        math::Function<math::Vector3D(const math::Point3D&)> m_normal_perturbator;
        Primitive m_perturbee;
    };
}

Primitive raytracer::primitives::bumpify(math::Function<math::Vector3D(const math::Point2D&)> function, Primitive primitive)
{
    return Primitive(std::make_shared<Bumpifier2DImplementation>(function, primitive));
}

Primitive raytracer::primitives::bumpify(math::Function<math::Vector3D(const math::Point3D&)> function, Primitive primitive)
{
    return Primitive(std::make_shared<Bumpifier3DImplementation>(function, primitive));
}
