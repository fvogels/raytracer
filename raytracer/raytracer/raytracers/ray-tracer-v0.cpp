#include "raytracers/ray-tracer-v0.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV0::trace(const Scene& scene, const Ray& ray) const
{
    Hit hit;

    if (scene.root->find_first_positive_hit(ray, &hit))
    {
        return TraceResult(colors::white(), hit.group_id, ray, hit.t);
    }
    else
    {
        return TraceResult::no_hit(ray);
    }
}

raytracer::RayTracer raytracer::raytracers::v0()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV0>());
}