#include "raytracing/fast-ray-tracer.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


raytracer::raytracers::_private_::FastRayTracer::FastRayTracer(unsigned recursion_limit)
    : m_recursion_limit(recursion_limit)
{
    // NOP
}

color raytracer::raytracers::_private_::FastRayTracer::trace(const Scene& scene, const Ray& ray) const
{
    return trace(scene, ray, m_recursion_limit);
}

color raytracer::raytracers::_private_::FastRayTracer::trace(const Scene& scene, const math::Ray& ray, unsigned recursions_left) const
{
    if (!recursions_left)
    {
        return colors::black();
    }
    else
    {
        Hit hit;
        color result = colors::black();

        if (scene.root->find_hit(ray, &hit))
        {
            assert(hit.material);

            auto material_properties = hit.material->at(hit.local_position);

            for (auto light_source : scene.light_sources)
            {
                for (auto& light_ray : light_source->lightrays_to(hit.position))
                {
                    Vector3D reflected_ray_direction = ray.direction.reflect_by(hit.normal).normalized();
                    auto direction_back_to_eye = -ray.direction.normalized();

                    Hit lighthit;

                    if (!scene.root->find_hit(light_ray.ray, &lighthit) || lighthit.t > 0.99999)
                    {
                        auto incoming = light_ray.ray.direction.normalized();
                        color reflected_color = material_properties.brdf(incoming, light_ray.color, hit.normal, direction_back_to_eye);

                        result += reflected_color;
                    }

                    if (material_properties.reflective)
                    {
                        Ray reflected_ray(hit.position + 0.00001 * reflected_ray_direction, reflected_ray_direction);
                        color reflection_color = trace(scene, reflected_ray, recursions_left - 1);
                        result += material_properties.brdf(-reflected_ray_direction, reflection_color, hit.normal, direction_back_to_eye);
                    }
                }
            }
        }

        return result;
    }
}

std::shared_ptr<RayTracer> raytracer::raytracers::fast_ray_tracer(unsigned recursion_limit)
{
    return std::make_shared<raytracer::raytracers::_private_::FastRayTracer>(recursion_limit);
}