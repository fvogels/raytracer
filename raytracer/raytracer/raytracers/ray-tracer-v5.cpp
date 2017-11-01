#include "raytracers/ray-tracer-v5.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


raytracer::raytracers::_private_::RayTracerV5::RayTracerV5(double minimum_weight)
    : m_minimum_weight(minimum_weight)
{
    // NOP
}

TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene& scene, const Ray& ray) const
{
    return trace(scene, ray, 1.0);
}

TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene& scene, const Ray& eye_ray, double weight) const
{
    assert(weight >= 0);

    if (weight >= m_minimum_weight)
    {
        Hit hit;

        if (scene.root->find_first_positive_hit(eye_ray, &hit))
        {
            assert(hit.material);

            Color result = colors::black();
            auto material_properties = hit.material->at(hit.local_position);

            result += compute_ambient(material_properties);
            result += this->process_lights(scene, material_properties, hit, eye_ray);
            result += compute_reflection(scene, material_properties, hit, eye_ray, weight);

            return TraceResult(result, hit.group_id, eye_ray, hit.t);
        }
        else
        {
            return TraceResult::no_hit(eye_ray);
        }
    }
    else
    {
        return TraceResult::no_hit(eye_ray);
    }
}

Color raytracer::raytracers::_private_::RayTracerV5::compute_reflection(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    if (material_properties.reflectivity > 0)
    {
        Vector3D reflected = eye_ray.direction.reflect_by(hit.normal);
        Ray secondary_ray(hit.position + reflected * 0.00001, reflected);

        return material_properties.reflectivity * trace(scene, secondary_ray, weight * material_properties.reflectivity).color;
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
