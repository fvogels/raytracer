#include "primitives/resizer-primitive.h"
#include "primitives/transformer-primitive.h"


using namespace raytracer;


Primitive raytracer::primitives::resize_x(Primitive child, double size)
{
    double factor = size / child->bounding_box().x().size();

    return scale(factor, 1, 1, child);
}

Primitive raytracer::primitives::resize_y(Primitive child, double size)
{
    double factor = size / child->bounding_box().y().size();

    return scale(1, factor, 1, child);
}

Primitive raytracer::primitives::resize_z(Primitive child, double size)
{
    double factor = size / child->bounding_box().z().size();

    return scale(1, 1, factor, child);
}

Primitive raytracer::primitives::resize_x_uniform(Primitive child, double size)
{
    double factor = size / child->bounding_box().x().size();

    return scale(factor, factor, factor, child);
}

Primitive raytracer::primitives::resize_y_uniform(Primitive child, double size)
{
    double factor = size / child->bounding_box().y().size();

    return scale(factor, factor, factor, child);
}

Primitive raytracer::primitives::resize_z_uniform(Primitive child, double size)
{
    double factor = size / child->bounding_box().z().size();

    return scale(factor, factor, factor, child);
}
