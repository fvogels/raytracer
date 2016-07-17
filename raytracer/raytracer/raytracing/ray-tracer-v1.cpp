#include "raytracing/ray-tracer-v1.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


color raytracer::raytracers::_private_::RayTracerV1::trace(const Scene& scene, const Ray& ray) const
{
    Hit hit;
    color result = colors::black();

    if (scene.root->find_hit(ray, &hit))
    {
        assert(hit.material);

        auto material_properties = hit.material->at(hit.local_position);

        result += compute_ambient(material_properties);
    }

    return result;
}

color raytracer::raytracers::_private_::RayTracerV1::compute_ambient(const MaterialProperties& properties) const
{
    return properties.ambient;
}

raytracer::RayTracer raytracer::raytracers::v1()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV1>());
}