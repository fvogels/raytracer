#include "raytracers/ray-tracer-v6.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


namespace
{
    
}

raytracer::RayTracer raytracer::raytracers::v6(double minimum_weight)
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>(minimum_weight));
}