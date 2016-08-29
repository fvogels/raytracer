#include "materials/material-transformer.h"

using namespace raytracer;

namespace
{
    class Material2DTransformer : public raytracer::materials::_private_::Material2D
    {

    };
}


Material raytracer::materials::transform2d(Material material, const math::Transformation& transformation)
{

}