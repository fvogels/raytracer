#include "raytracers/ray-tracer-v7.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


Color raytracer::raytracers::_private_::RayTracerV7::determine_color(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    Color result = colors::black();

    result += RayTracerV6::determine_color(scene, material_properties, hit, eye_ray, weight);
    result += compute_see_through_color(scene, material_properties, hit, eye_ray, weight);

    return result;
}

Color raytracer::raytracers::_private_::RayTracerV7::compute_see_through_color(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
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

raytracer::RayTracer raytracer::raytracers::v7(double minimum_weight)
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV7>(minimum_weight));
}
