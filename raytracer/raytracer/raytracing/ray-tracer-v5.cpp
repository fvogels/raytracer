#include "raytracing/ray-tracer-v5.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


raytracer::raytracers::_private_::RayTracerV5::RayTracerV5(double minimum_weight)
    : m_minimum_weight(minimum_weight)
{
    // NOP
}

color raytracer::raytracers::_private_::RayTracerV5::trace(const Scene& scene, const Ray& ray) const
{
    return trace(scene, ray, 1.0);
}

color raytracer::raytracers::_private_::RayTracerV5::trace(const Scene& scene, const Ray& ray, double weight) const
{
    assert(weight >= 0);

    if (weight < m_minimum_weight)
    {
        Hit hit;
        color result = colors::black();

        if (scene.root->find_hit(ray, &hit))
        {
            assert(hit.material);

            auto material_properties = hit.material->at(hit.local_position);

            result += compute_ambient(material_properties);

            for (auto light_source : scene.light_sources)
            {
                for (auto light_ray : light_source->lightrays_to(hit.position))
                {
                    result += compute_diffuse(material_properties, hit, ray, light_ray);
                    result += compute_specular(material_properties, hit, ray, light_ray);
                }
            }

            result += compute_reflection(scene, material_properties, hit, ray, weight);
        }

        return result;
    }
    else
    {
        return colors::black();
    }
}

color raytracer::raytracers::_private_::RayTracerV5::compute_reflection(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    if (material_properties.reflectivity > 0)
    {
        Vector3D reflected = eye_ray.direction.reflect_by(hit.normal);
        Ray secundary_ray(hit.position + reflected * 0.00001, reflected);

        return material_properties.reflectivity * trace(scene, secundary_ray, weight * material_properties.reflectivity);
    }
    else
    {
        return colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::v5(double minimum_weight)
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>(minimum_weight));
}