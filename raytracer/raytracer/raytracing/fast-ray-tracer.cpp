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
            const Vector3D& hit_normal = hit.normal;            

            for (auto light_source : scene.light_sources)
            {
                for (auto light_ray : light_source->lightrays_to(hit.position))
                {
                    Vector3D reflected_ray_direction = ray.direction.reflect_by(hit.normal).normalized();
                    auto direction_back_to_eye = -ray.direction.normalized();

                    Hit lighthit;

                    if (!scene.root->find_hit(light_ray.ray, &lighthit) || lighthit.t > 0.99999)
                    {
                        auto incoming = light_ray.ray.direction.normalized();

                        // Ambient
                        {
                            result += material_properties.ambient * light_ray.color;
                        }

                        // Diffuse
                        {
                            assert(hit_normal.is_unit());
                            assert(incoming.is_unit());
                            double cos = -hit_normal.dot(incoming);
                            assert(cos <= 1);

                            if (cos > 0)
                            {
                                result += material_properties.diffuse * light_ray.color * cos;
                            }
                        }

                        // Specular
                        if ( material_properties.specular != colors::black() )
                        {
                            assert(hit_normal.is_unit());
                            assert(incoming.is_unit());
                            Vector3D reflected = ray.direction.reflect_by(hit_normal).normalized();
                            double cos = -reflected.dot(incoming);
                            assert(cos <= 1);

                            if (cos > 0)
                            {
                                result += material_properties.specular * light_ray.color * pow(cos, material_properties.specular_exponent);
                            }
                        }
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