#include "cameras/displaceable-camera.h"
#include <assert.h>

using namespace math;


raytracer::cameras::_private_::DisplaceableCamera::DisplaceableCamera(const Matrix4D& transformation)
    : m_transformation(transformation)
{
    // NOP
}

std::vector<math::Ray> raytracer::cameras::_private_::DisplaceableCamera::create_rays(const math::Point2D& p) const
{
    auto untransformed_rays = create_untransformed_rays(p);

    std::vector<math::Ray> transformed_rays;
    for (auto& untransformed_ray : untransformed_rays)
    {
        auto transformed_ray = untransformed_ray.transform(m_transformation);

        transformed_rays.push_back(transformed_ray);
    }

    return transformed_rays;
}