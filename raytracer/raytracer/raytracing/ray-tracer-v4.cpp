#include "raytracing/ray-tracer-v4.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


color raytracer::raytracers::_private_::RayTracerV4::trace(const Scene& scene, const Ray& ray) const
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
                Hit lighthit;

                if (!scene.root->find_hit(light_ray.ray, &lighthit) || lighthit.t > 0.99999)
                {
                    result += compute_diffuse(material_properties, hit, ray, light_ray);
                    result += compute_specular(material_properties, hit, ray, light_ray);
                }
            }
        }
    }

    return result;
}

raytracer::RayTracer raytracer::raytracers::v4()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}