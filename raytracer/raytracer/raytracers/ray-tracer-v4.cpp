#include "raytracers/ray-tracer-v4.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


imaging::Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(
    const Scene& scene,
    const MaterialProperties& material_properties,
    const Hit& hit,
    const math::Ray& eye_ray,
    const LightRay& light_ray) const
{
    Hit lighthit;
    const double limit = m_noisy ? 1 : 0.99999;

    if (!scene.root->find_first_positive_hit(light_ray.ray, &lighthit) || lighthit.t > limit)
    {
        return RayTracerV3::process_light_ray(scene, material_properties, hit, eye_ray, light_ray);
    }
    else
    {
        return colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::v4()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>(false));
}

raytracer::RayTracer raytracer::raytracers::noisy_v4()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>(true));
}