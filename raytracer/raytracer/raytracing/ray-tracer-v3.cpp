#include "raytracing/ray-tracer-v3.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


color raytracer::raytracers::_private_::RayTracerV3::trace(const Scene& scene, const Ray& ray) const
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
    }

    return result;
}

color raytracer::raytracers::_private_::RayTracerV3::compute_specular(const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, const LightRay& light_ray) const
{
    if (material_properties.specular != colors::black())
    {
        assert(hit_normal.is_unit());
        assert(incoming.is_unit());
        Vector3D reflected = eye_ray.direction.reflect_by(hit.normal).normalized();
        double cos = -reflected.dot(eye_ray.direction.normalized());
        assert(Interval<double>(0, 1).contains(cos));

        if (cos > 0)
        {
            return material_properties.specular * light_ray.color * pow(cos, material_properties.specular_exponent);
        }
        else
        {
            return colors::black();
        }
    }
}

raytracer::RayTracer raytracer::raytracers::v3()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}