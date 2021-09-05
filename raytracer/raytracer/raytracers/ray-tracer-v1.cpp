#include "raytracers/ray-tracer-v1.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV1::trace(const Scene& scene, const Ray& eye_ray) const
{
    Hit hit;

    if (scene.root->find_first_positive_hit(eye_ray, &hit))
    {
        assert(hit.material);

        auto material_properties = hit.material->at(hit.local_position);
        auto c = determine_color(scene, material_properties, hit, eye_ray);
        
        return TraceResult(c, hit.group_id, eye_ray, hit.t);
    }
    else
    {
        return TraceResult::no_hit(eye_ray);
    }
}

Color raytracer::raytracers::_private_::RayTracerV1::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray&) const
{
    return compute_ambient(properties);
}

Color raytracer::raytracers::_private_::RayTracerV1::compute_ambient(const MaterialProperties& properties) const
{
    return properties.ambient;
}

raytracer::RayTracer raytracer::raytracers::v1()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV1>());
}