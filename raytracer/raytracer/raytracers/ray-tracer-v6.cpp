#include "raytracers/ray-tracer-v6.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const Ray& eye_ray, double weight) const
{
    assert(weight >= 0);

    if (weight >= m_minimum_weight)
    {
        Hit hit;

        if (scene.root->find_first_positive_hit(eye_ray, &hit))
        {
            assert(hit.material);

            auto material_properties = hit.material->at(hit.local_position);
            Color own_result = compute_own_color(scene, material_properties, hit, eye_ray, weight * material_properties.opacity);
            Color see_through_result = compute_see_through_color(scene, material_properties, hit, eye_ray, weight * (1 - material_properties.opacity));
            Color result = own_result + see_through_result;

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

Color raytracer::raytracers::_private_::RayTracerV6::compute_own_color(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    Color result = colors::black();

    if (material_properties.opacity > 0)
    {
        result += compute_ambient(material_properties);
        result += this->process_lights(scene, material_properties, hit, eye_ray);
        result += compute_reflection(scene, material_properties, hit, eye_ray, weight);
    }

    return result * material_properties.opacity;
}

Color raytracer::raytracers::_private_::RayTracerV6::compute_see_through_color(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    if (material_properties.opacity < 1)
    {
        Ray through_ray(hit.position + eye_ray.direction * 0.00001, eye_ray.direction);

        return trace(scene, through_ray, weight).color * (1 - material_properties.opacity);
    }
    else
    {
        return colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::v6(double minimum_weight)
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>(minimum_weight));
}
