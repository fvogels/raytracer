#include "lights/light-ray.h"

raytracer::LightRay::LightRay(const math::Ray& ray, const imaging::color& color)
    : ray(ray), color(color)
{
    // NOP
}