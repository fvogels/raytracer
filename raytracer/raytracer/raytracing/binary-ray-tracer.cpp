#include "raytracing/binary-ray-tracer.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


color raytracer::raytracers::_private_::BinaryRayTracer::trace(const Scene& scene, const Ray& ray) const
{
    Hit hit;

    if (scene.root->find_hit(ray, &hit))
    {
        return colors::white();
    }
    else
    {
        return colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::binary(double weight_bound)
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::BinaryRayTracer>());
}