#include "raytracing/ray-tracer-v2.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


color raytracer::raytracers::_private_::RayTracerV2::trace(const Scene& scene, const Ray& eye_ray) const
{
    Hit hit;
    color result = colors::black();

    if (scene.root->find_hit(eye_ray, &hit))
    {
        assert(hit.material);

        auto material_properties = hit.material->at(hit.local_position);

        result += compute_ambient(material_properties);
        result += process_lights(scene, material_properties, hit, eye_ray);
        
    }

    return result;
}

imaging::color raytracer::raytracers::_private_::RayTracerV2::process_lights(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray) const
{
    color result = colors::black();

    for (auto light_source : scene.light_sources)
    {
        result += process_light_source(scene, material_properties, hit, eye_ray, light_source);
    }

    return result;
}

imaging::color raytracer::raytracers::_private_::RayTracerV2::process_light_source(
    const Scene& scene,
    const MaterialProperties& material_properties, 
    const Hit& hit,
    const math::Ray& eye_ray,
    LightSource light_source) const
{
    color result = colors::black();

    for (auto light_ray : light_source->lightrays_to(hit.position))
    {
        result += process_light_ray(scene, material_properties, hit, eye_ray, light_ray);
    }

    return result;
}

imaging::color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(
    const Scene& scene,
    const MaterialProperties& material_properties,
    const Hit& hit,
    const math::Ray& eye_ray,
    const LightRay& light_ray) const
{
    color result = colors::black();

    result += compute_diffuse(material_properties, hit, eye_ray, light_ray);

    return result;
}

color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, const LightRay& light_ray) const
{
    Vector3D incoming = light_ray.ray.direction.normalized();

    assert(hit.normal.is_unit());
    double cos = -hit.normal.dot(incoming);
    assert(Interval<double>(-1, 1).contains(cos));

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