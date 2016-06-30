#include "raytracing/monte-carlo-ray-tracer.h"

using namespace imaging;
using namespace math;


raytracer::raytracers::_private_::MonteCarloRayTracer::MonteCarloRayTracer(unsigned recursion_limit)
    : m_recursion_limit(recursion_limit) { }

color raytracer::raytracers::_private_::MonteCarloRayTracer::trace(const Scene& scene, const Ray& ray) const
{
    return trace(scene, ray, m_recursion_limit);
}

color raytracer::raytracers::_private_::MonteCarloRayTracer::trace(const Scene& scene, const Ray& ray, unsigned recursions_left) const
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

                    int count = 0;
                    color total = colors::black();

                    for (double azimuth = 0; azimuth < 360; azimuth += 10)
                    {
                        for (double altitude = -90; altitude <= 90; altitude += 10)
                        {
                            Vector3D direction(1, degrees(azimuth), degrees(altitude));

                            if (direction.dot(hit.normal) > 0)
                            {
                                Ray r(hit.position + 0.00001 * direction, direction);
                                color c = trace(scene, r, recursions_left - 1);

                                total += material_properties.brdf(-direction, c, hit.normal, direction_back_to_eye);
                                ++count;
                            }
                        }
                    }

                    result += (total / count);
                }
            }
        }

        return result;
    }
}

std::shared_ptr<raytracer::RayTracer> monte_carlo(unsigned recursion_limit)
{
    return std::make_shared<raytracer::raytracers::_private_::MonteCarloRayTracer>(recursion_limit);
}