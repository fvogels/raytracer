#include "raytracers/ray-tracer-v2.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


Color raytracer::raytracers::_private_::RayTracerV2::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& eye_ray) const
{
    auto result = colors::black();

    result += RayTracerV1::determine_color(scene, properties, hit, eye_ray);
    result += process_lights(scene, properties, hit, eye_ray);

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_lights(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray) const
{
    Color result = colors::black();

    for (auto light_source : scene.light_sources)
    {
        result += process_light_source(scene, material_properties, hit, eye_ray, light_source);
    }

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_source(
    const Scene& scene,
    const MaterialProperties& material_properties, 
    const Hit& hit,
    const math::Ray& eye_ray,
    LightSource light_source) const
{
    Color result = colors::black();

    for (auto light_ray : light_source->lightrays_to(hit.position))
    {
        result += process_light_ray(scene, material_properties, hit, eye_ray, light_ray);
    }

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(
    const Scene&,
    const MaterialProperties& material_properties,
    const Hit& hit,
    const math::Ray& eye_ray,
    const LightRay& light_ray) const
{
    Color result = colors::black();

    result += compute_diffuse(material_properties, hit, eye_ray, light_ray);

    return result;
}

Color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, const LightRay& light_ray) const
{
    Vector3D incoming = light_ray.ray.direction.normalized();

    assert(hit.normal.is_unit());
    double cos = -hit.normal.dot(incoming);
    assert(interval(-1.0, 1.0).contains(cos));

    if (cos > 0)
    {
        return material_properties.diffuse * light_ray.color * cos;
    }
    else
    {
        return colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::v2()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
}
