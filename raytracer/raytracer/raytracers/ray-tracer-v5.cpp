#include "raytracers/ray-tracer-v5.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


imaging::Color raytracer::raytracers::_private_::RayTracerV5::process_light_ray(
    const Scene& scene,
    const MaterialProperties& material_properties,
    const Hit& hit,
    const math::Ray& eye_ray,
    const LightRay& light_ray) const
{
    const double limit = 0.99999;
    auto hits = scene.root->find_all_hits(light_ray.ray);
    Color filter = colors::white();

    for (auto& hit : hits)
    {
        if (hit->t < 0)
            continue;

        if (hit->t > limit)
            break;

        auto mp = hit->material->at(hit->local_position);

        filter *= mp.light_filtering;

        if (filter == colors::black())
            break;
    }

    if (filter != colors::black())
    {
        LightRay filtered_light_ray(light_ray.ray, light_ray.color * filter);

        return RayTracerV3::process_light_ray(scene, material_properties, hit, eye_ray, filtered_light_ray);
    }
    else
    {
        return colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::v5()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}
