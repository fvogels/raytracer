#include "raytracing/ray-tracer-v1.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV1::trace(const Scene& scene, const Ray& ray) const
{
    Hit hit;

    if (scene.root->find_hit(ray, &hit))
    {
        assert(hit.material);

        auto material_properties = hit.material->at(hit.local_position);
        auto c = compute_ambient(material_properties);
        
        return TraceResult(c, hit.group_id);
    }
    else
    {
        return TraceResult::no_hit();
    }
}

color raytracer::raytracers::_private_::RayTracerV1::compute_ambient(const MaterialProperties& properties) const
{
    return properties.ambient;
}

raytracer::RayTracer raytracer::raytracers::v1()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV1>());
}