#include "raytracers/ray-tracer-v3.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


imaging::Color raytracer::raytracers::_private_::RayTracerV3::process_light_ray(
    const Scene& scene,
    const MaterialProperties& material_properties,
    const Hit& hit,
    const math::Ray& eye_ray,
    const LightRay& light_ray) const
{
    Color result = colors::black();

    result += RayTracerV2::process_light_ray(scene, material_properties, hit, eye_ray, light_ray);
    result += compute_specular(material_properties, hit, eye_ray, light_ray);

    return result;
}

Color raytracer::raytracers::_private_::RayTracerV3::compute_specular(const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, const LightRay& light_ray) const
{
    if (material_properties.specular != colors::black())
    {
        assert(hit.normal.is_unit());
        Vector3D reflected = eye_ray.direction.reflect_by(hit.normal).normalized();
        double cos = -reflected.dot(light_ray.ray.direction.normalized());

        assert(interval(-1.0, 1.0).contains(cos));

        if (cos > 0)
        {
            return material_properties.specular * light_ray.color * pow(cos, material_properties.specular_exponent);
        }
        else
        {
            return colors::black();
        }
    }
    else
    {
        return colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::v3()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}